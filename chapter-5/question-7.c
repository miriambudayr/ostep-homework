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

        // The result is that the child doesn't print, but the parent does.
        fclose(stdout);
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    }
    else
    {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
    }
}