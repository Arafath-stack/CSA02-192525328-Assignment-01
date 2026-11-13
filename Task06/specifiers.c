#include <stdio.h>
int main(void)
{
    int i = 162;  unsigned u = 65535u;  long l = 5000000000L;  long long ll = 80000000000LL;
    float f = 2.25f;  double d = 4.50;  char c = 'R';  const char *s = "Rs";
    printf("%%d  int       : %d\n", i);
    printf("%%u  unsigned  : %u\n", u);
    printf("%%ld long      : %ld\n", l);
    printf("%%lld long long: %lld\n", ll);
    printf("%%f  float/dbl : %f %f\n", f, d);
    printf("%%c  char      : %c\n", c);
    printf("%%s  string    : %s\n", s);
    printf("\n--- wrong specifier test ---\n");
    printf("long 5000000000 printed with %%d  : %d\n", l);
    long paise = 16250;
    printf("\n%ld paise printed as rupees: Rs %ld.%02ld\n", paise, paise / 100, paise % 100);
    return 0;
}
