#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (rc == 0)
    {
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        // wc is equal to -1. I guess it makes sense, since it doesn't have a child to wait for.
        int wc = wait(NULL);
        printf("wc equals %d\n", wc);
    }
    else
    {
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
        // wc is equal to the PID of child.
        // int wc = wait(NULL);
        // printf("wc equals %d\n", wc);
    }
}