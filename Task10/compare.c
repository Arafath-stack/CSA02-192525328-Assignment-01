#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include "billing.h"

int main(void)
{
    int sizes[] = {4000, 60000, 800000};
    printf("%8s | %16s | %16s | %14s | %14s | %s\n", "n", "paise (long long)", "int total(wrap)", "float Rs", "double Rs", "float error Rs");
    for (int k = 0; k < 3; k++) {
        int n = sizes[k];
        int       t_int = 0;  long t_long = 0;  long long t_ll = 0;
        float     t_f = 0;    double t_d = 0;
        for (int i = 0; i < n; i++) {
            unsigned int u = (unsigned)((i * 37 + 11) % 450);
            long b = compute_bill(u);
            t_int  = (int)((unsigned)t_int + (unsigned)b);   /* wraps like 32-bit hardware */
            t_long += b;
            t_ll   += b;
            t_f    += (float)b / 100.0f;
            t_d    += (double)b / 100.0;
        }
        printf("%8d | %16lld | %16d | %14.2f | %14.4f | %.2f\n", n, t_ll, t_int, t_f, t_d, t_f - t_ll / 100.0);
        printf("         int overflow? %s   long overflow? %s   long long overflow? no (max %lld)\n",
               (long long)t_int != t_ll ? "YES" : "no", (long long)t_long != t_ll ? "YES" : "no", LLONG_MAX);
    }
    printf("\nStandard minimum vs this system:\n");
    printf("  short     : standard >= 2 bytes, here %zu\n", sizeof(short));
    printf("  int       : standard >= 2 bytes, here %zu\n", sizeof(int));
    printf("  long      : standard >= 4 bytes, here %zu\n", sizeof(long));
    printf("  long long : standard >= 8 bytes, here %zu\n", sizeof(long long));

    printf("\nWhen does double lose accuracy? 2^53 = 9007199254740992\n");
    double big = 9007199254740992.0;
    printf("  (double)2^53 + 1 == 2^53 ? %s\n", (big + 1.0 == big) ? "yes - the +1 is lost" : "no");
    printf("  district total is about 4.1e10 paise, far below 2^53 (9.0e15): double stays exact for integers here\n");
    printf("  but double rupees with fractions (0.01) are NOT exact, so error accumulates\n");

    const long N = 100000000L;
    volatile long long a = 0;  volatile double d = 0.0;
    clock_t t0 = clock();
    for (long i = 0; i < N; i++) a += 12345;
    clock_t t1 = clock();
    for (long i = 0; i < N; i++) d += 12345.0;
    clock_t t2 = clock();
    printf("\nTime per addition: long long %.2f ns, double %.2f ns\n",
           1e9 * (t1 - t0) / CLOCKS_PER_SEC / N, 1e9 * (t2 - t1) / CLOCKS_PER_SEC / N);
    printf("Space per variable: long long %zu bytes, double %zu bytes\n", sizeof(long long), sizeof(double));
    return 0;
}
