#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// TO COMPILE AND RUN
// gcc question-2.c -o main && ./main

// QUESTION:
// Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e. at the same time?

int main()
{
    int fd = open("file.txt", O_RDONLY, O_CREAT);
    // printf("fd = %d\n", fd);
    printf("fd = %d\n", fd);
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (rc == 0)
    {
        printf("hello, I am child (pid:%d) (fd:%d)\n", (int)getpid(), fd);
        write(fd, "child", 5);
    }
    else
    {
        printf("hello, I am parent of %d (pid:%d) (fd:%d)\n", rc, (int)getpid(), fd);
        write(fd, "parent", 6);
    }
}