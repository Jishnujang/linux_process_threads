#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    // Create FIFO if not exists
    mkfifo(FIFO_PATH, 0666);

    // Open FIFO for writing
    int fd = open(FIFO_PATH, O_WRONLY);

    // Write the number to FIFO
    write(fd, &num, sizeof(int));

    // Close the FIFO
    close(fd);

    return 0;
}
