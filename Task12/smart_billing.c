/* Task 12: smart-meter billing with time-of-day tariff and run-time tariff file.
   Readings are in watt-hours (Wh) per 15-minute interval.
   Money is accumulated in units of 1/10000 paise (exact integers) and rounded ONCE
   (half up) at the end of the bill. */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#define SLOTS_PER_DAY   96            /* 24 h x 4                      */
#define DAYS_PER_MONTH  30
#define SCALE           10000ULL      /* 100 (percent) x 100 (paise)   */
#define WH_PER_UNIT     1000ULL       /* 1 unit = 1 kWh = 1000 Wh      */

typedef struct {
    uint64_t slab1_units, slab2_units;          /* units                  */
    uint64_t rate1, rate2, rate3;               /* paise per unit         */
    uint64_t fixed_paise;
    uint64_t peak_percent;                      /* 120 means +20 percent  */
    uint32_t peak_start_hour, peak_end_hour;
} tariff_t;

static int load_tariff(const char *file, tariff_t *t)
{
    FILE *f = fopen(file, "r");
    if (!f) { printf("ERROR: cannot open tariff file %s\n", file); return 0; }
    char key[64]; unsigned long long val; int found = 0;
    while (fscanf(f, " %63s %llu", key, &val) == 2) {
        if      (!strcmp(key, "slab1_units"))     { t->slab1_units = val; found |= 1; }
        else if (!strcmp(key, "slab2_units"))     { t->slab2_units = val; found |= 2; }
        else if (!strcmp(key, "rate1_paise"))     { t->rate1 = val;       found |= 4; }
        else if (!strcmp(key, "rate2_paise"))     { t->rate2 = val;       found |= 8; }
        else if (!strcmp(key, "rate3_paise"))     { t->rate3 = val;       found |= 16; }
        else if (!strcmp(key, "fixed_paise"))     { t->fixed_paise = val; found |= 32; }
        else if (!strcmp(key, "peak_percent"))    { t->peak_percent = val; found |= 64; }
        else if (!strcmp(key, "peak_start_hour")) { t->peak_start_hour = (uint32_t)val; found |= 128; }
        else if (!strcmp(key, "peak_end_hour"))   { t->peak_end_hour = (uint32_t)val; found |= 256; }
        else { printf("ERROR: unknown key %s\n", key); fclose(f); return 0; }
    }
    fclose(f);
    if (found != 511) { printf("ERROR: tariff file incomplete\n"); return 0; }
    if (t->slab1_units > t->slab2_units || t->peak_start_hour >= t->peak_end_hour || t->peak_end_hour > 24) {
        printf("ERROR: tariff values inconsistent\n"); return 0;
    }
    return 1;
}

static int is_peak(const tariff_t *t, int slot)          /* slot 0..95 */
{
    uint32_t hour = (uint32_t)slot / 4;
    return hour >= t->peak_start_hour && hour < t->peak_end_hour;
}

/* Bill one house for a month. Cumulative energy decides the slab of every Wh. */
static uint64_t bill_month(const tariff_t *t, const uint32_t *wh, int n,
                           uint64_t *total_wh_out, uint64_t *peak_wh_out)
{
    uint64_t cum = 0, peak_wh = 0, cost = 0;      /* cost in 1/10000 paise */
    uint64_t b1 = t->slab1_units * WH_PER_UNIT, b2 = t->slab2_units * WH_PER_UNIT;
    for (int i = 0; i < n; i++) {
        uint64_t left = wh[i];
        uint64_t mult = is_peak(t, i % SLOTS_PER_DAY) ? t->peak_percent : 100;
        if (is_peak(t, i % SLOTS_PER_DAY)) peak_wh += left;
        while (left > 0) {                         /* split reading at slab boundary */
            uint64_t rate, room;
            if (cum < b1)      { rate = t->rate1; room = b1 - cum; }
            else if (cum < b2) { rate = t->rate2; room = b2 - cum; }
            else               { rate = t->rate3; room = left; }
            uint64_t part = left < room ? left : room;
            cost += part * rate * mult;            /* Wh x paise/kWh x percent = 1/(1000*100) paise... */
            cum += part;  left -= part;
        }
    }
    *total_wh_out = cum;  *peak_wh_out = peak_wh;
    /* cost is in (Wh x paise/unit x percent) = 1000 x 100 = 100000 per paise */
    return t->fixed_paise + (cost + (WH_PER_UNIT * 100) / 2) / (WH_PER_UNIT * 100);
}

static void print_money(uint64_t p) { printf("Rs %" PRIu64 ".%02" PRIu64, p / 100, p % 100); }

static void largest_values(void)
{
    uint64_t max_w = 15000, wh_reading = max_w / 4;                 /* 15 kW for 15 minutes */
    uint64_t month = wh_reading * SLOTS_PER_DAY * DAYS_PER_MONTH;
    uint64_t year  = wh_reading * 35040ULL;
    uint64_t district_year = year * 800000ULL;
    printf("Assumption: maximum connection 15 kW, flat out all the time.\n");
    printf("  one 15-minute reading   : %" PRIu64 " Wh      (fits in 16 bits? %s)\n", wh_reading, wh_reading <= 65535 ? "yes" : "no");
    printf("  one house, one month    : %" PRIu64 " Wh (fits in 16 bits? %s; in 32 bits? %s)\n", month, month <= 65535 ? "yes" : "NO", month <= 4294967295ULL ? "yes" : "no");
    printf("  one house, one year     : %" PRIu64 " Wh (in 32 bits? %s)  = %" PRIu64 " kWh (in 16 bits? %s)\n", year, year <= 4294967295ULL ? "yes" : "NO", year / 1000, year / 1000 <= 65535 ? "yes" : "NO");
    printf("  district (800000), year : %" PRIu64 " Wh (in 32 bits? %s; in 64 bits? %s)\n", district_year, district_year <= 4294967295ULL ? "yes" : "NO", "yes");
    printf("  readings per house/year : 35040 (4 x 24 x 365)\n");
    printf("  district readings/year  : %" PRIu64 " (> INT_MAX 2147483647: needs 64-bit counter)\n", (uint64_t)(35040ULL * 800000ULL));
    uint64_t cost_year_house = year * 450ULL * 120ULL;
    printf("  one house year, cost accumulator Wh x 450 x 120 = %" PRIu64 " (32-bit? %s, 64-bit? yes)\n", cost_year_house, cost_year_house <= 4294967295ULL ? "yes" : "NO");
}

int main(int argc, char **argv)
{
    const char *cfg = argc > 1 ? argv[1] : "tariff.cfg";
    int constant_mode = argc > 2 ? atoi(argv[2]) : 0;     /* 0 = daily pattern, else constant Wh */
    tariff_t t;
    if (!load_tariff(cfg, &t)) return 1;
    printf("Tariff file: %s  (slabs %" PRIu64 "/%" PRIu64 ", rates %" PRIu64 "/%" PRIu64 "/%" PRIu64 " paise, peak %" PRIu64 "%% for %u:00-%u:00)\n",
           cfg, t.slab1_units, t.slab2_units, t.rate1, t.rate2, t.rate3, t.peak_percent, t.peak_start_hour, t.peak_end_hour);

    int n = SLOTS_PER_DAY * DAYS_PER_MONTH;
    uint32_t *wh = malloc((size_t)n * sizeof *wh);
    for (int i = 0; i < n; i++) {
        int slot = i % SLOTS_PER_DAY;
        if (constant_mode) wh[i] = (uint32_t)constant_mode;
        else wh[i] = is_peak(&t, slot) ? 200 + (uint32_t)((i * 13) % 11) : 60 + (uint32_t)((i * 13) % 11);
    }
    uint64_t total_wh, peak_wh;
    uint64_t bill = bill_month(&t, wh, n, &total_wh, &peak_wh);
    printf("Readings processed : %d\n", n);
    printf("Total energy       : %" PRIu64 " Wh (%" PRIu64 ".%03" PRIu64 " units)\n", total_wh, total_wh / 1000, total_wh % 1000);
    printf("Peak-hour energy   : %" PRIu64 " Wh\n", peak_wh);
    printf("Monthly bill       : "); print_money(bill); printf("\n");
    free(wh);
    if (argc > 3) { printf("\n"); largest_values(); }
    return 0;
}
