// Copyright 2019 David Johnston

package threads;

public class Main {
  public static void main(String[] args) {
    for (int i = 0; i < 10; i++) {
      new Thread(() -> System.out.println("Thread ID: " + Thread.currentThread().getId())).start();
    }
  }
}
