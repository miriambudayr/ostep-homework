#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define _GNU_SOURCE /* See feature_test_macros(7) */
#include <sched.h>

// Used this as a reference:
// https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
int main(int argc, char *argv[])
{
    int cpu;
    getcpu(cpu);
    printf("cpu: %d", cpu);
    int fds_pipe1[2]; // Used to store two ends of the first pipe.
    int fds_pipe2[2]; // Used to store two ends of the second pipe.

    char fixed_str[] = "meow";

    // The pid_t data type represents process IDs.
    // https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_554.html
    pid_t p;

    if (pipe(fds_pipe1) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    if (pipe(fds_pipe2) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    printf("input string: %s\n", fixed_str);
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork failed");
        return 1;
    }

    // parent process.
    else if (p > 0)
    {
        char concat_str[100];
        close(fds_pipe1[0]); // close reading end of first pipe

        // write input string and close writing end of first pipe.
        write(fds_pipe1[1], fixed_str, strlen(fixed_str) + 1);
        close(fds_pipe1[1]);

        // wait for child to send a string.
        wait(NULL);

        // close writing end of second pipe.
        close(fds_pipe2[1]);

        // read string from child, print it and close reading end.
        read(fds_pipe2[0], concat_str, 100);
        printf("Concatenated string %s\n", concat_str);
        close(fds_pipe2[0]);
    }
    // child process
    else
    {
        // close writing end of first pipe.
        close(fds_pipe1[1]);

        // read a string using first pipe.
        char concat_str[100];
        read(fds_pipe1[0], concat_str, 100);

        // concatenate a fixed string with it
        int k = strlen(concat_str);
        int i;
        for (i = 0; i < strlen(fixed_str); i++)
            concat_str[k++] = fixed_str[i];

        // string ends with '\0'.
        // QUESTION: why didn't the first string end with this character?
        concat_str[k] = '\0';

        // close both reading ends.
        close(fds_pipe1[0]);
        close(fds_pipe2[0]);

        // write concatenated string and close writing end
        write(fds_pipe2[1], concat_str, strlen(concat_str) + 1);
        close(fds_pipe2[1]);

        exit(0);
    }
}
