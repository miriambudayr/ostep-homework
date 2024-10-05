#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int p1_write = open("process1_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int p1_read = open("process1_read.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (p1_write < 0)
    {
        perror("r1");
    }

    if (p1_read < 0)
    {
        perror("w1");
    }

    int p1_writeable_fds[2] = {p1_read, p1_write};
    int p1_writeable = pipe(p1_writeable_fds);

    if (p1_writeable == -1)
    {
        printf("could not open pipe\n");
        return EXIT_FAILURE;
    }

    int sz;

    sz = write(p1_write, "hello geeks\n", strlen("hello geeks\n"));

    printf("called write(% d, \"hello geeks\\n\", %ld)."
           " It returned %d\n",
           p1_write, strlen("hello geeks\n"), sz);

    // close(p1_write);

    // Try to read from the READ file.

    FILE *file_ptr;
    char read_char_buffer;

    file_ptr = fopen("process1_read.txt", "r");

    if (NULL == file_ptr)
    {
        printf("File cannot be opened\n");
        return EXIT_FAILURE;
    }

    printf("Contents of the file are:\n");

    while ((read_char_buffer = fgetc(file_ptr)) != EOF)
    {
        printf("%c", read_char_buffer);
    }

    fclose(file_ptr);
    return 0;
}
