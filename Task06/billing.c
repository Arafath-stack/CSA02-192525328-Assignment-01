#include <stdio.h>
#include "billing.h"

/* Units used; unsigned 16-bit arithmetic makes roll-over automatic. */
unsigned int consumption(meter_t previous, meter_t current)
{
    return (meter_t)(current - previous);
}

/* Bill in paise (integer) -> no rounding error is possible. */
long compute_bill(unsigned int units)
{
    long paise = FIXED_CHARGE_PAISE;
    unsigned int s1 = MIN(units, SLAB1_UNITS);
    unsigned int s2 = 0, s3 = 0;

    if (units > SLAB1_UNITS)
        s2 = MIN(units, SLAB2_UNITS) - SLAB1_UNITS;
    if (units > SLAB2_UNITS)
        s3 = units - SLAB2_UNITS;
#ifdef DEBUG
    printf("[DEBUG] units=%u slab1=%u slab2=%u slab3=%u\n", units, s1, s2, s3);
#endif
    paise += (long)s1 * RATE1_PAISE + (long)s2 * RATE2_PAISE + (long)s3 * RATE3_PAISE;
    return paise;
}

/* Rejects negative, out-of-range and "decreasing without roll-over" readings.
   A roll-over (e.g. 65400 -> 120) gives 256 units, which is plausible;
   1530 -> 1200 would give 65206 units, which is impossible. */
int validate_readings(long previous, long current)
{
    if (previous < 0 || current < 0)               return READ_NEGATIVE;
    if (previous > MAX_READING || current > MAX_READING) return READ_TOO_BIG;
    if (consumption((meter_t)previous, (meter_t)current) > MAX_MONTHLY_UNITS)
        return READ_DECREASE;
    return READ_OK;
}

void print_money(long paise)
{
    printf("Rs %ld.%02ld", paise / 100, paise % 100);
}
