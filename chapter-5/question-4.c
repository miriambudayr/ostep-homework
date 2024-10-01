
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// TO COMPILE AND RUN:
// gcc question-4.c -o main && ./main

// One question was why I think there are so many different ways to call `exec`. I think perhaps ergonomics?
// https://stackoverflow.com/a/55744093
// Looks like I was pretty much right, except one detail: if you use `execv` it requires a vector of objects rather than a list of objects. Having a list of objects is useful if you know what the arguments are at compile-time. Otherwise if you need a user to pass arguments in, you can use a vector.

int main(int argc, char *argv[])
{
    // The const char *arg0 and subsequent ellipses in the execl(), execlp(), and execle() functions can be thought of as arg0, arg1, ..., argn.Together they describe a list of one or more pointers to null - terminated strings that represent the argument list available to the executed program.The first argument, by convention, should point to the file name associated with the file being executed.The list of arguments must be terminated by a NULL pointer.

    // printf("%d", execl("/bin/ls", "ls", ".", NULL));
    // printf("%d", execle("/bin/ls", "ls", ".", NULL));
    // printf("%d", execlp("/bin/ls", "ls", ".", NULL));

    // The execv(),
    //     execvp(), and execvP() functions provide an array of pointers to null - terminated strings that represent the argument list available to the new program.The first argument, by convention, should point to the file name associated with the file being executed.The array of pointers must be terminated by a NULL pointer.

    // Define the argument array, terminated by NULL
    char *const a[] = {"ls", ".", NULL};

    // Use execv to execute /bin/ls with the arguments in a
    printf("%d", execv("/bin/ls", a));
}