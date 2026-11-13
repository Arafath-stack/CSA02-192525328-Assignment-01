#include <stdio.h>
long compute_bill(unsigned int units);   /* declared but never defined */
int main(void)
{
    printf("%ld\n", compute_bill(100));
    return 0;
}
