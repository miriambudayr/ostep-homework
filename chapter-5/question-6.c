#include <stdio.h>
#include <stdlib.h>
// Imports getpid
#include <unistd.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    int status;

    if (rc < 0)
    {
        fprintf(stderr, "failed to fork\n");
    }
    else if (rc == 0)
    {
        printf("child process (pid: %d)\n", (int)getpid());
        return 0;
    }
    else
    {
        // Homework asks why this would be useful. It could be useful if you want to communicate the child's status
        // information up to the parent.
        // I heavily used this documentation: https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-waitpid-wait-specific-child-process-end
        int wcpid = waitpid(rc, &status, WCONTINUED);
        printf("parent process of %d (pid:%d) (child_status: %d)\n", rc, (int)getpid(), status);
    }
}