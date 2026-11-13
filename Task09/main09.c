/* Interactive billing program: reads many houses until end of input. */
#include <stdio.h>
#include "billing.h"

int main(void)
{
    int house, count = 0;  long prev, cur, total = 0;
    printf("Enter: house previous current  (Ctrl-D to finish)\n");
    for (;;) {
        int r = scanf("%d %ld %ld", &house, &prev, &cur);
        if (r == EOF) break;
        if (r != 3) {
            printf("Invalid input (letters or missing value) - skipping the rest of the line.\n");
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) ;
            continue;
        }
        int v = validate_readings(prev, cur);
        if (v == READ_NEGATIVE) { printf("House %d: rejected - negative reading\n", house); continue; }
        if (v == READ_TOO_BIG)  { printf("House %d: rejected - reading above 65535\n", house); continue; }
        if (v == READ_DECREASE) { printf("House %d: rejected - current < previous without roll-over\n", house); continue; }
        unsigned int units = consumption((meter_t)prev, (meter_t)cur);
        long bill = compute_bill(units);
        printf("House %d: %u units, bill ", house, units); print_money(bill); printf("\n");
        total += bill; count++;
    }
    printf("Bills issued: %d, total collected: ", count); print_money(total); printf("\n");
    return 0;
}
