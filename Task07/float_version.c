/* Alternative: all arithmetic in float rupees, rounded only once at the end. */
#include <stdio.h>
#include <math.h>
#include "billing.h"

static float bill_float(int units)            /* rupees in float */
{
    float r = 50.0f;
    if (units > 200) r += (units - 200) * 4.50f;
    if (units > 100) r += ((units > 200 ? 200 : units) - 100) * 2.25f;
    return r;
}
int main(void)
{
    int sizes[] = {10, 100, 1000, 4000, 60000, 800000};
    printf("%8s %18s %18s %14s\n", "n", "float total (Rs)", "exact paise (Rs)", "error (Rs)");
    for (int k = 0; k < 6; k++) {
        float  tf = 0.0f;  long tp = 0;
        for (int i = 0; i < sizes[k]; i++) {
            int u = (i * 37 + 11) % 450;
            tf += bill_float(u);
            tp += compute_bill(u);
        }
        double exact = tp / 100.0;
        printf("%8d %18.2f %18.2f %14.2f\n", sizes[k], tf, exact, tf - exact);
    }
    return 0;
}
