#include <stdio.h>
int main(void)
{
    int unused_variable;
    int n = -1;  unsigned int u = 1;
    if (n < u) printf("minus one is less than one\n");
    long big = 5000000000L;
    printf("%d\n", big);
    return 0;
}
