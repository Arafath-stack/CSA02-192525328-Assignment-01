#include <stdio.h>
#include "billing.h"

int main(void)
{
    meter_t prev = 1200, cur = 1530;
    unsigned int u = consumption(prev, cur);
    printf("Units = %u\n", u);
    long b = compute_bill(u);
    printf("Bill  = "); print_money(b); printf("\n");
    return 0;
}
