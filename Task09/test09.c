/* Automatic test table + alternative slab-array (loop) design. */
#include <stdio.h>
#include "billing.h"

/* ---- alternative design: slabs in arrays, loop over s slabs ---- */
static const unsigned int limit[3] = {SLAB1_UNITS, SLAB2_UNITS, 0xFFFFFFFFu};
static const long         rate[3]  = {RATE1_PAISE, RATE2_PAISE, RATE3_PAISE};
static long bill_loop(unsigned int units)
{
    long paise = FIXED_CHARGE_PAISE;
    unsigned int lower = 0;
    for (int s = 0; s < 3 && units > lower; s++) {
        unsigned int upper = limit[s] < units ? limit[s] : units;
        paise += (long)(upper - lower) * rate[s];
        lower = limit[s];
    }
    return paise;
}

static int pass = 0, fail = 0;
static void check_bill(const char *name, unsigned int units, long expected)
{
    long got = compute_bill(units);
    int ok = (got == expected);
    printf("%-28s units=%5u expected=Rs %4ld.%02ld actual=Rs %4ld.%02ld  %s\n",
           name, units, expected / 100, expected % 100, got / 100, got % 100, ok ? "PASS" : "FAIL");
    ok ? pass++ : fail++;
}
static void check_valid(const char *name, long p, long c, int expected)
{
    int got = validate_readings(p, c);
    int ok = (got == expected);
    printf("%-28s prev=%6ld cur=%6ld expected code=%d actual code=%d  %s\n", name, p, c, expected, got, ok ? "PASS" : "FAIL");
    ok ? pass++ : fail++;
}

int main(void)
{
    printf("== Slab and boundary tests ==\n");
    check_bill("zero units",            0,   5000);
    check_bill("slab 1 (50 units)",     50,  5000);
    check_bill("exactly 100 units",     100, 5000);
    check_bill("slab 2 (150 units)",    150, 16250);
    check_bill("exactly 200 units",     200, 27500);
    check_bill("slab 3 (350 units)",    350, 95000);

    printf("\n== Roll-over test ==\n");
    unsigned int u = consumption(65400, 120);
    printf("consumption(65400,120) = %u (expected 256)  %s\n", u, u == 256 ? "PASS" : "FAIL");
    u == 256 ? pass++ : fail++;
    check_bill("bill for rolled-over meter", u, 5000 + 100 * 225 + 56 * 450);

    printf("\n== Reading validation ==\n");
    check_valid("normal reading",          1200, 1530, READ_OK);
    check_valid("roll-over 65535 -> 0",    65535, 0,   READ_OK);
    check_valid("negative previous",       -5, 100,    READ_NEGATIVE);
    check_valid("negative current",        100, -20,   READ_NEGATIVE);
    check_valid("above register limit",    100, 70000, READ_TOO_BIG);
    check_valid("current<previous no roll",1530, 1200, READ_DECREASE);

    printf("\n== Five bills totalled by hand ==\n");
    unsigned int five[5] = {80, 120, 180, 260, 500};
    long hand[5] = {5000, 9500, 23000, 54500, 162500};
    long total = 0, hand_total = 254500;
    for (int i = 0; i < 5; i++) { check_bill("hand-calculated bill", five[i], hand[i]); total += compute_bill(five[i]); }
    printf("Total by program = Rs %ld.%02ld, by hand = Rs %ld.%02ld  %s\n", total / 100, total % 100,
           hand_total / 100, hand_total % 100, total == hand_total ? "PASS" : "FAIL");
    total == hand_total ? pass++ : fail++;

    printf("\n== Alternative design: loop over slab arrays agrees with if-version for 0..5000 units ==\n");
    int mismatches = 0;
    for (unsigned int k = 0; k <= 5000; k++) if (bill_loop(k) != compute_bill(k)) mismatches++;
    printf("mismatches = %d  %s\n", mismatches, mismatches == 0 ? "PASS" : "FAIL");
    mismatches == 0 ? pass++ : fail++;

    printf("\nSUMMARY: %d passed, %d failed\n", pass, fail);
    return fail != 0;
}
