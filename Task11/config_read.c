/* Alternative: tariff read from a config file at start-up. Measures start-up cost. */
#include <stdio.h>
#include <time.h>

int main(void)
{
    FILE *f = fopen("tariff.cfg", "w");
    fprintf(f, "100 200 0 225 450 5000\n");
    fclose(f);

    const int REPS = 100000;
    long v[6] = {0};
    clock_t t0 = clock();
    for (int r = 0; r < REPS; r++) {
        f = fopen("tariff.cfg", "r");
        fscanf(f, "%ld %ld %ld %ld %ld %ld", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5]);
        fclose(f);
    }
    clock_t t1 = clock();
    printf("Tariff read from file: %ld %ld %ld %ld %ld %ld\n", v[0], v[1], v[2], v[3], v[4], v[5]);
    printf("Start-up cost to read t=6 values: %.2f microseconds per run\n", 1e6 * (t1 - t0) / CLOCKS_PER_SEC / REPS);
    printf("Space: 6 x %zu bytes = %zu bytes\n", sizeof(long), 6 * sizeof(long));
    return 0;
}
