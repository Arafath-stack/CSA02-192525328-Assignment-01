#include <stdio.h>
#include "billing.h"
#define DEBUG_LEVEL 2            /* replaced by the preprocessor */
/* this comment is removed by the preprocessor */
int main(void)
{
    unsigned int u = consumption(1200, 1530);
    long b = compute_bill(u);
    printf("Units=%u Bill=", u); print_money(b); printf("\n");
    return 0;
}
