public class BoundedBuffer {
    private static final int BUFFER_SIZE = 5;
    private int count; // number of items in the buffer
    private int in; // points to the next free position in the buffer
    private int out; // points to the next full position in the buffer
    private Object[] buffer;

    public BoundedBuffer() {
        // buffer is initially empty
        count = 0;
        in = 0;
        out = 0;
        buffer = new Object[BUFFER_SIZE];
    }

    // producer calls this method
    public synchronized void insert(Object item) {
        while (count == BUFFER_SIZE) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        System.out.println("Producer Entered " + item + " Buffer Size = " + count);
        notifyAll();
    }

    // consumer calls this method
    public synchronized Object remove() {
        while (count == 0) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        Object item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        System.out.println("Consumer Consumed " + item + " Buffer " + (count == 0 ? "EMPTY" : "Size = " + count));
        notifyAll();
        return item;
    }
}