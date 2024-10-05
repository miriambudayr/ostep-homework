#include <sys/time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // gettimeofday(struct timeval *restrict tp, void *restrict tzp);
    printf("yo\n");

    struct timeval tp;

    int t0 = gettimeofday(&tp, 0);
    int t1 = gettimeofday(&tp, 0);

    printf("time of day is %d\n", tp.tv_usec);
}