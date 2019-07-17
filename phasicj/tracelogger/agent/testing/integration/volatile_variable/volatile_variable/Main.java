// Copyright 2019 David Johnston

package volatile_variable;

public class Main {

    static volatile int var;

    public static void main(String[] args) {
        (new Thread(new Reader())).start();
        (new Thread(new Writer())).start();
    }
}

class Reader implements Runnable {
    public void run() {
        System.out.println(Main.var);
    }
}

class Writer implements Runnable {
    public void run() {
        Main.var = 17;
    }
}