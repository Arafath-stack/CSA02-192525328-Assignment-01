#include <stdio.h>
#include <string.h>
typedef unsigned short meter_t;

int main(void)
{
    printf("--- Surprise 1: integer division ---\n");
    int units = 250;
    double hundreds = units / 100;            /* integer division happens first */
    printf("units/100 = %.2f (expected 2.50); 5/2 = %d\n", hundreds, 5 / 2);

    printf("\n--- Surprise 2: integer promotion of unsigned short ---\n");
    meter_t m = 65535;
    printf("m + 1          = %d   (promoted to int, no wrap)\n", m + 1);
    printf("(meter_t)(m+1) = %d   (cast brings roll-over back)\n", (meter_t)(m + 1));

    printf("\n--- Surprise 3: casting a large long to int ---\n");
    long big = 5000000000L;
    printf("(int)5000000000L = %d\n", (int)big);

    printf("\n--- Surprise 4: signed/unsigned comparison ---\n");
    int neg = -1; unsigned int one = 1;
    printf("(-1 < 1u) is %d   (-1 became 4294967295)\n", neg < one);

    printf("\n--- Surprise 5: floating point equality ---\n");
    printf("0.1 + 0.2 == 0.3 ? %d\n", 0.1 + 0.2 == 0.3);

    printf("\n--- Rounding rule: round half up in integer paise ---\n");
    long base = 333;                          /* paise */
    long trunc_ = base * 120 / 100;
    long round_ = (base * 120 + 50) / 100;
    printf("333 paise + 20%% : truncated=%ld, rounded=%ld (exact 399.6)\n", trunc_, round_);
    return 0;
}
