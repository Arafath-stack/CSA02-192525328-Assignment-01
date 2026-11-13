#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    printf("%-20s %6s  %s\n", "Type", "Bytes", "Range");
    printf("%-20s %6zu  %d to %d\n", "char", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("%-20s %6zu  0 to %u\n", "unsigned short", sizeof(unsigned short), (unsigned)USHRT_MAX);
    printf("%-20s %6zu  %d to %d\n", "short", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("%-20s %6zu  %d to %d\n", "int", sizeof(int), INT_MIN, INT_MAX);
    printf("%-20s %6zu  0 to %u\n", "unsigned int", sizeof(unsigned), UINT_MAX);
    printf("%-20s %6zu  %ld to %ld\n", "long", sizeof(long), LONG_MIN, LONG_MAX);
    printf("%-20s %6zu  %lld to %lld\n", "long long", sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("%-20s %6zu  max %e, %d digits, epsilon %e\n", "float", sizeof(float), FLT_MAX, FLT_DIG, FLT_EPSILON);
    printf("%-20s %6zu  max %e, %d digits, epsilon %e\n", "double", sizeof(double), DBL_MAX, DBL_DIG, DBL_EPSILON);

    printf("\nDistrict check: 800000 bills x Rs 1000 max = 8.0e10 paise\n");
    printf("  int max  = %d  -> NOT enough\n", INT_MAX);
    printf("  long max = %ld -> enough on this system\n", LONG_MAX);

    printf("\nRoll-over of 16-bit register:\n");
    unsigned short r = 65535;
    r = r + 1;
    printf("  65535 + 1 stored in unsigned short = %hu\n", r);

    /* float vs paise: 4000 bills of Rs 123.45 */
    float  total_f = 0.0f;
    long   total_p = 0;
    for (int i = 0; i < 4000; i++) { total_f += 123.45f; total_p += 12345L; }
    printf("\n4000 bills of Rs 123.45 (correct total = Rs 493800.00)\n");
    printf("  float rupees total : Rs %.2f   <-- WRONG\n", total_f);
    printf("  long paise total   : Rs %ld.%02ld   <-- exact\n", total_p / 100, total_p % 100);
    return 0;
}
