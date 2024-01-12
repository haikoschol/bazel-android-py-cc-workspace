// https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

int main(int argc, char** argv)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(":memory:", &DB);

    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }

    std::string create = "CREATE TABLE PERSON("
                      "ID INT PRIMARY KEY     NOT NULL, "
                      "NAME           TEXT    NOT NULL, "
                      "SURNAME          TEXT     NOT NULL, "
                      "AGE            INT     NOT NULL, "
                      "ADDRESS        CHAR(50), "
                      "SALARY         REAL );";

	exit = sqlite3_exec(DB, create.c_str(), callback, NULL, &errorMessage);

    if (exit) {
        std::cerr << "Error create table " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }

	string insert("INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
			"INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);"
			"INSERT INTO PERSON VALUES(3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0);");

	exit = sqlite3_exec(DB, insert.c_str(), NULL, 0, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(errorMessage);
	}
	else
		std::cout << "Records created Successfully!" << std::endl;

	cout << "STATE OF TABLE AFTER INSERT" << endl;

	string query = "SELECT * FROM PERSON;";
	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);
	return (0);
}

