#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int p1_write = open("process1_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    int sz;

    if (p1_write < 0)
    {
        perror("r1");
    }

    sz = write(p1_write, "hello geeks\n", strlen("hello geeks\n"));

    printf("called write(% d, \"hello geeks\\n\", %ld)."
           " It returned %d\n",
           p1_write, strlen("hello geeks\n"), sz);

    close(p1_write);

    // Read and print the file

    FILE *file_ptr;
    char read_char_buffer;

    // What is the difference between open and fopen?
    file_ptr = fopen("process1_write.txt", "r");

    if (NULL == file_ptr)
    {
        printf("File cannot be opened\n");
        return EXIT_FAILURE;
    }

    printf("Contents of the file are:-: \n");

    // Printing contents of file character by character in a loop.

    while ((read_char_buffer = fgetc(file_ptr)) != EOF)
    {
        printf("%c", read_char_buffer);
    }

    fclose(file_ptr);
    return 0;
}
