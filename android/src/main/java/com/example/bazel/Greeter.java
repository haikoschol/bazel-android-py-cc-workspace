package com.example.bazel;

import java.io.IOException;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

/**
 * A tiny Greeter library for the Bazel Android "Hello, World" app.
 */
public class Greeter {
  OkHttpClient client = new OkHttpClient();
  
  public String sayHello() {
    Request request = new Request.Builder().url("https://google.com").build();

    try (Response response = client.newCall(request).execute()) {
      if (response.isSuccessful()) {
        return "Hello Bazel! \uD83D\uDC4B\uD83C\uDF31"; // Unicode for 👋🌱
      } else {
        return "Google said: " + response.message();
      }
    } catch (IOException ex) {
      return "GET request failed: " + ex.toString();
    }
  }
}
