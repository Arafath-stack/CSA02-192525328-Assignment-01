#define SQUARE_BAD(x) x * x
#define SQUARE(x)     ((x) * (x))
#define MAX(a, b)     (((a) > (b)) ? (a) : (b))
#define SLAB1_UNITS   100
int main(void)
{
    int a = 3, i = 5, j = 3;
    int p = SQUARE_BAD(a + 1);
    int q = SQUARE(a + 1);
    int m = MAX(i++, j);
    int s = SLAB1_UNITS + 1;
    return p + q + m + s;
}
