#include <stdio.h>
#include "billing.h"
int read_house(int *house, long *prev, long *cur);
int main(void)
{
    int h; long p, c;
    if (!read_house(&h, &p, &c)) { printf("bad input\n"); return 1; }
    if (validate_readings(p, c)) { printf("rejected\n"); return 2; }
    printf("House %d: ", h); print_money(compute_bill(consumption((meter_t)p, (meter_t)c))); printf("\n");
    return 0;
}
