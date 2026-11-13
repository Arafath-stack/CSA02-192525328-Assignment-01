#include "billing.h"
unsigned int consumption(meter_t previous, meter_t current) { return (meter_t)(current - previous); }
long compute_bill(unsigned int units)
{
    long p = FIXED_CHARGE_PAISE;
    if (units > SLAB2_UNITS) p += (long)(units - SLAB2_UNITS) * RATE3_PAISE;
    if (units > SLAB1_UNITS) p += (long)(MIN(units, SLAB2_UNITS) - SLAB1_UNITS) * RATE2_PAISE;
    return p;
}
int validate_readings(long previous, long current)
{
    if (previous < 0 || current < 0) return READ_NEGATIVE;
    if (previous > MAX_READING || current > MAX_READING) return READ_TOO_BIG;
    return consumption((meter_t)previous, (meter_t)current) > MAX_MONTHLY_UNITS ? READ_DECREASE : READ_OK;
}
