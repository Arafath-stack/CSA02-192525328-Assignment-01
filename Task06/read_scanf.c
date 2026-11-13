#include <stdio.h>
#include "billing.h"

int main(void)
{
    int  house;
    long prev, cur;
    printf("Enter house no, previous reading, current reading: ");
    if (scanf("%d %ld %ld", &house, &prev, &cur) != 3) {   /* check return value */
        printf("Invalid input: enter three whole numbers.\n");
        return 1;
    }
    int v = validate_readings(prev, cur);
    if (v != READ_OK) { printf("Rejected (code %d)\n", v); return 2; }
    unsigned int units = consumption((meter_t)prev, (meter_t)cur);
    long bill = compute_bill(units);
    printf("House %d | units %u | fixed Rs 50.00 | total ", house, units);
    print_money(bill);
    printf("\n");
    return 0;
}
