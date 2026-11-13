#include <stdio.h>
int main(void)
{
    int n = -1;  unsigned int u = 1;
    if (n < 0 || (unsigned int)n < u) printf("minus one is less than one\n");
    long big = 5000000000L;
    printf("%ld\n", big);
    return 0;
}
