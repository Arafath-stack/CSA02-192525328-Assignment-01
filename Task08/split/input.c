#include <stdio.h>
#include "billing.h"
int read_house(int *house, long *prev, long *cur)
{
    return scanf("%d %ld %ld", house, prev, cur) == 3;
}
