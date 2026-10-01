public class Consumer extends Thread {
    private BoundedBuffer buffer;

    public Consumer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        for (int i = 0; i < 20; i++)
            buffer.remove();
    }
}