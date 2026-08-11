import java.util.Scanner;

public class Task1 {

    static class ChildThread extends Thread {
        private int n;
        private long result;

        public ChildThread(int n) {
            this.n = n;
        }

        public void run() {
            result = 0;

            for (int i = 1; i <= 2 * n; i++) {
                result += i;
            }
        }

        public long getResult() {
            return result;
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a positive integer: ");
        int n = scanner.nextInt();

        ChildThread child = new ChildThread(n);
        child.start();

        long parentResult = 0;

        for (int i = 1; i <= n; i++) {
            parentResult += i;
        }

        child.join();

        long childResult = child.getResult();

        long finalResult = parentResult + childResult;

        System.out.println("Parent thread result: " + parentResult);
        System.out.println("Child thread result: " + childResult);
        System.out.println("Final result: " + finalResult);

        scanner.close();
    }
}