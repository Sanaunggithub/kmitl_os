public class Producer extends Thread {
    private BoundedBuffer buffer;

    public Producer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        for (int i = 0; i < 20; i++)
            buffer.insert(i);
    }
}