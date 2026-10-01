public class Main {
    public static void main(String[] args) throws InterruptedException {
        BoundedBuffer buffer = new BoundedBuffer();
        Producer producer = new Producer(buffer);
        Consumer consumer = new Consumer(buffer);
        producer.start();
        consumer.start();
        producer.join();
        consumer.join();
    }
}