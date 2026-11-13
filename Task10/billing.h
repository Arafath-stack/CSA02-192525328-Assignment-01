#ifndef BILLING_H            /* include guard: stops double inclusion */
#define BILLING_H

/* ---- Tariff constants: change ONLY here for a tariff revision ---- */
#define SLAB1_UNITS        100      /* first 100 units            */
#define SLAB2_UNITS        200      /* units 101 to 200           */
#define RATE1_PAISE        0        /* first slab is free         */
#define RATE2_PAISE        225      /* Rs 2.25 per unit           */
#define RATE3_PAISE        450      /* Rs 4.50 per unit above 200 */
#define FIXED_CHARGE_PAISE 5000L    /* Rs 50 fixed charge         */

/* ---- Meter limits ---- */
#define MAX_READING        65535    /* 16-bit register            */
#define MAX_MONTHLY_UNITS  5000     /* assumption: no house uses more */

/* ---- Safe macros ---- */
#define RUPEES_TO_PAISE(r) ((r) * 100L)
#define MAX(a, b)          (((a) > (b)) ? (a) : (b))
#define MIN(a, b)          (((a) < (b)) ? (a) : (b))

typedef unsigned short meter_t;

/* return codes of validate_readings */
enum { READ_OK = 0, READ_NEGATIVE, READ_TOO_BIG, READ_DECREASE };

unsigned int consumption(meter_t previous, meter_t current);
long         compute_bill(unsigned int units);
int          validate_readings(long previous, long current);
void         print_money(long paise);

#endif
