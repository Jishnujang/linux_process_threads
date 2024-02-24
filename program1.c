#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FIFO_PATH "/tmp/myfifo"

int num;  // Declare num as an integer variable

void *thread1(void *arg) {
    int *num = (int *)arg;
    int square = (*num) * (*num);
    printf("In thread 1: square = %d\n", square);

    // Pass the square value to thread 2
    return (void *)(intptr_t)square;
}

void *thread2(void *arg) {
    int *square = (int *)arg;

    int result = num + *square;
    printf("In thread 2: square of num + num = %d\n", result);

    // Pass the result value to the main thread
    return (void *)(intptr_t)result;
}

int main() {
    pthread_t tid1, tid2;
    int square;

    // Create FIFO if not exists
    mkfifo(FIFO_PATH, 0666);

    // Create child process
    if (fork() == 0) {
        // Inside child process (program2)
        execl("./program2", "./program2", NULL);
        exit(0);
    } else {
        // Inside parent process (program1)

        // Wait for the child process to terminate
        wait(NULL);

        // Open FIFO for reading
        int fd = open(FIFO_PATH, O_RDONLY);

        // Read the number from FIFO
        read(fd, &num, sizeof(int));

        // Close the FIFO
        close(fd);

        // Create thread 1
        pthread_create(&tid1, NULL, thread1, (void *)&num);
        pthread_join(tid1, (void **)&square);

        // Create thread 2
        pthread_create(&tid2, NULL, thread2, (void *)&square);
        pthread_join(tid2, (void **)&square);

        // In main thread (parent process)
        printf("In main thread: return value from thread 2: %d\n", square);
    }

    return 0;
}

