#include <stdio.h>
#include "billing.h"
void print_money(long paise) { printf("Rs %ld.%02ld", paise / 100, paise % 100); }
