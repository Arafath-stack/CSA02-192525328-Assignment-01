/* Alternative: money as double rupees, rounded once per bill. */
#include <stdio.h>
#include <math.h>
int main(void)
{
    int n[] = {4000, 60000, 800000};
    for (int k = 0; k < 3; k++) {
        double sum = 0.0;  long paise = 0;
        for (int i = 0; i < n[k]; i++) {
            double bill = 123.45;                 /* rupees */
            sum   += bill;
            paise += 12345L;
        }
        printf("n=%6d  double total=%.6f  exact=%ld.%02ld  error=%.3e Rs\n",
               n[k], sum, paise / 100, paise % 100, sum - paise / 100.0);
    }
    return 0;
}
