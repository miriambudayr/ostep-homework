// Example program

// TO COMPILE AND RUN:
// gcc question-1.c -o main && ./main

// NOTE: You can uncomment my other experiments below if you want to run them. I tried to keep this organized!

// QUESTION:
// Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g. x) and set its value to something (e.g. 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?

// ANSWERS:
// Change x before fork: both the parent and child see the updated value when it is changed before `fork` is called.
// Change x in parent: the parent sees the updated value, but the child does not.
// Change x in child: the child sees the updated value, but the parent does not.
// Change x RIGHT after fork: both parent and child see updated value. But I am pretty sure they don't see the same `x`. I think there are two "copies" of that variable --- one in parent's memory space, and another in the child's.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 10;

// Change x RIGHT after fork.
int main(int argc, char *argv[])
{
    int rc = fork();
    x = 100;
    printf("meow (pid:%d) (x:%d)\n", (int)getpid(), x);
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (rc == 0)
    {
        printf("hello, I am child (pid:%d) (x:%d)\n", (int)getpid(), x);
    }
    else
    {
        printf("hello, I am parent of %d (pid:%d) (x:%d)\n",
               rc, (int)getpid(), x);
        int wc = wait(NULL);
    }
    return 0;
}

// Third part of question: change x to 100 in the child.
// int main(int argc, char *argv[])
// {
//     int rc = fork();
//     printf("meow (pid:%d) (x:%d)\n", (int)getpid(), x);
//     if (rc < 0)
//     {
//         fprintf(stderr, "fork failed\n");
//     }
//     else if (rc == 0)
//     {
//         x = 100;
//         printf("hello, I am child (pid:%d) (x:%d)\n", (int)getpid(), x);
//     }
//     else
//     {
//         printf("hello, I am parent of %d (pid:%d) (x:%d)\n",
//                rc, (int)getpid(), x);
//         int wc = wait(NULL);
//     }
//     return 0;
// }

// // Second part of question: change x to 100 in the parent.
// int main(int argc, char *argv[])
// {
//     int rc = fork();
//     printf("meow (pid:%d) (x:%d)\n", (int)getpid(), x);
//     if (rc < 0)
//     {
//         fprintf(stderr, "fork failed\n");
//     }
//     else if (rc == 0)
//     {

//         printf("hello, I am child (pid:%d) (x:%d)\n", (int)getpid(), x);
//     }
//     else
//     {
//         x = 100;
//         printf("hello, I am parent of %d (pid:%d) (x:%d)\n",
//                rc, (int)getpid(), x);
//         int wc = wait(NULL);
//     }
//     return 0;
// }

// First part of the question: change x to 100.
// int main(int argc, char *argv[])
// {
//     x = 100;
//     int rc = fork();
//     printf("meow (pid:%d) (x:%d)\n", (int)getpid(), x);
//     if (rc < 0)
//     {
//         fprintf(stderr, "fork failed\n");
//     }
//     else if (rc == 0)
//     {

//         printf("hello, I am child (pid:%d) (x:%d)\n", (int)getpid(), x);
//     }
//     else
//     {
//         int wc = wait(NULL);
//         printf("hello, I am parent of %d (pid:%d) (x:%d)\n",
//                rc, (int)getpid(), x);
//     }
//     return 0;
// }
