#include <stdio.h>
#define SQUARE_BAD(x)  x * x                 /* WRONG: no parentheses */
#define SQUARE(x)      ((x) * (x))           /* correct */
#define MAX_BAD(a, b)  a > b ? a : b         /* WRONG */
#define MAX(a, b)      (((a) > (b)) ? (a) : (b))
#define RUPEES_TO_PAISE(r) ((r) * 100L)

static inline int max_fn(int a, int b)    { return a > b ? a : b; }
static inline int square_fn(int x)        { return x * x; }

int main(void)
{
    int a = 3;
    printf("SQUARE_BAD(a+1) = %d   (expected 16)\n", SQUARE_BAD(a + 1));
    printf("SQUARE(a+1)     = %d\n", SQUARE(a + 1));

    int x = 4, y = 9;
    printf("10 + MAX_BAD(x,y)? -> %d  (expected 19)\n", 10 + MAX_BAD(x, y));
    printf("10 + MAX(x,y)       -> %d\n", 10 + MAX(x, y));

    int i = 5, j = 3;
    int m = MAX(i++, j);
    printf("MAX(i++, j): result=%d, i=%d   (i incremented TWICE)\n", m, i);
    i = 5;
    m = max_fn(i++, j);
    printf("max_fn(i++, j): result=%d, i=%d (i incremented once)\n", m, i);

    printf("RUPEES_TO_PAISE(162) = %ld\n", RUPEES_TO_PAISE(162));
    printf("square_fn(a+1) = %d\n", square_fn(a + 1));
    return 0;
}
