package sleep;

public class Main {
    public static void main(String[] args) {
        try {
            Thread.sleep(100);
        } catch (InterruptedException ex) {
            throw new RuntimeException();
        }
    }
}