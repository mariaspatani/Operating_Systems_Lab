#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // Fork failed
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("24SJPCCSL407 ");
    }
    else {
        // Parent process
        wait(NULL);  // Wait for child to finish
        printf("Operating Systems Lab");
    }

    return 0;
}
