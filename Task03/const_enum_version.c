/* Alternative: tariff as const variables and enum instead of #define. */
#include <stdio.h>
enum { SLAB1_UNITS = 100, SLAB2_UNITS = 200 };            /* integer constants, no storage */
static const long RATE1_PAISE = 0, RATE2_PAISE = 225, RATE3_PAISE = 450;
static const long FIXED_CHARGE_PAISE = 5000L;             /* typed, has an address, visible in gdb */

long compute_bill(int units)
{
    long paise = FIXED_CHARGE_PAISE;
    if (units > SLAB2_UNITS) paise += (units - SLAB2_UNITS) * RATE3_PAISE;
    if (units > SLAB1_UNITS) paise += ((units > SLAB2_UNITS ? SLAB2_UNITS : units) - SLAB1_UNITS) * RATE2_PAISE;
    paise += (units < SLAB1_UNITS ? units : SLAB1_UNITS) * RATE1_PAISE;
    return paise;
}
int main(void)
{
    int tests[] = {0, 100, 150, 200, 350};
    for (int i = 0; i < 5; i++) { long p = compute_bill(tests[i]); printf("%3d units -> Rs %ld.%02ld\n", tests[i], p/100, p%100); }
    printf("sizeof(RATE2_PAISE) = %zu bytes of storage; &RATE2_PAISE exists: %p\n", sizeof RATE2_PAISE, (void *)&RATE2_PAISE);
    return 0;
}
