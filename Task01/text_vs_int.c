/* Task 1 alternative concept: readings stored as text ("01530") vs integers. */
#include <stdio.h>
#include <string.h>
#include <time.h>

static int str_to_int(const char *s)      /* O(d): one step per digit */
{
    int v = 0;
    while (*s) { v = v * 10 + (*s - '0'); s++; }
    return v;
}

int main(void)
{
    const long N = 20000000L;
    char a[] = "01530", b[] = "01200";    /* d = 5 digits */
    volatile int sink = 0;
    volatile int ia = 1530, ib = 1200;

    clock_t t0 = clock();
    for (long i = 0; i < N; i++) {
        a[4] = (char)('0' + i % 10);
        sink += str_to_int(a) - str_to_int(b);     /* convert + compare */
    }
    clock_t t1 = clock();
    for (long i = 0; i < N; i++) {
        ia = 1530 + (int)(i % 10);
        sink += ia - ib;                           /* compare integers */
    }
    clock_t t2 = clock();

    printf("Text reading   : %zu bytes (d=5 chars + '\\0')\n", sizeof a);
    printf("Integer reading: %zu bytes (unsigned short)\n", sizeof(unsigned short));
    printf("Text   convert+compare: %.1f ns per reading\n", 1e9 * (t1 - t0) / CLOCKS_PER_SEC / N);
    printf("Integer compare      : %.1f ns per reading\n", 1e9 * (t2 - t1) / CLOCKS_PER_SEC / N);
    return 0;
}
