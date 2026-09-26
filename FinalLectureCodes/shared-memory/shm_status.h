#define NOT_READY -1
#define FILLED 0
#define TAKEN 1

// shared memory
struct Memory
{
    int status;
    int data[4];
};