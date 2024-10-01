#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void)
{
    int child_pid, second_child_pid, pipe_status;
    int pipe_fds[2];
    char buffer[BUFFER_SIZE];

    // Attempt to create a pipe
    if (pipe(pipe_fds) < 0)
    {
        fprintf(stderr, "Error: Unable to create pipe\n");
        exit(1);
    }

    // Fork the first child process
    child_pid = fork();
    if (child_pid < 0)
    {
        fprintf(stderr, "Error: Fork failed\n");
        exit(1);
    }
    else if (child_pid == 0)
    {
        // Inside the first child process, fork again
        second_child_pid = fork();
        if (second_child_pid < 0)
        {
            fprintf(stderr, "Error: Fork failed\n");
            exit(1);
        }

        if (second_child_pid == 0)
        {
            // Second child: read from the pipe
            close(pipe_fds[1]); // Close write-end of the pipe
            int bytes_read = read(pipe_fds[0], buffer, BUFFER_SIZE);
            if (bytes_read < 0)
            {
                fprintf(stderr, "Error: Unable to read from pipe\n");
                exit(1);
            }
            printf("Received message in second child process (PID: %d):\n", getpid());
            write(STDOUT_FILENO, buffer, bytes_read);
            exit(0);
        }
        else
        {
            // First child: write to the pipe
            close(pipe_fds[0]); // Close read-end of the pipe
            const char *message = "Hello from the first child process\n";
            write(pipe_fds[1], message, 31);
            exit(0);
        }
    }

    return 0;
}
