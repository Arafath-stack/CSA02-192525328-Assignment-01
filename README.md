# CSA02-192525328-Assignment1

**Name:** A. Yassar Arafath
**Register No:** 192525328
**Assignment:** CSA02 - Assignment 1: Reliable Billing Program for the Grama Jyothi Rural Electricity Co-operative (50 marks)
**Compiler:** gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0, C11/gnu17 default, Ubuntu 24.04, x86-64

Compile every program with warnings enabled, for example:

    gcc -Wall -Wextra file.c -o file

Programs that use the shared billing module are compiled together with it:

    gcc -Wall -Wextra main05.c billing.c -o billing_normal
    gcc -Wall -Wextra -DDEBUG main05.c billing.c -o billing_debug     # debug mode

Each folder contains the C source, `output.txt` (the real terminal output of every command run) and `output_screenshot.png` (the same output rendered as a terminal image).

| Folder | Content | How to run | Result |
|---|---|---|---|
| Task01 | Data analysis; text vs integer readings (`text_vs_int.c`) | `gcc text_vs_int.c -o t && ./t` | text reading 6 bytes / 13.8 ns, integer 2 bytes / 1.8 ns |
| Task02 | Data types, `consumption()` TODO, float failure | `gcc task02_complete.c -o t && ./t` | 330 and 256 units; float total Rs 493781.22 vs exact Rs 493800.00 |
| Task03 | Constants, `compute_bill()` TODO | `gcc task03_complete.c -o t && ./t` | Rs 50.00 / 50.00 / 162.50 / 275.00 / 950.00; RATE2=230 changes all bills consistently |
| Task04 | Macros, `gcc -E` | `gcc macros.c -o t && ./t`, `gcc -E expand_demo.c` | SQUARE_BAD(a+1)=7, SQUARE=16, MAX(i++,j) increments twice |
| Task05 | Header file, include guards, DEBUG mode | `gcc -DDEBUG main05.c billing.c -o t && ./t` | debug line printed only with -DDEBUG |
| Task06 | scanf/printf, validation, fgets+strtol | `gcc read_scanf.c billing.c -o t && echo '17 1200 1530' \| ./t` | Rs 860.00; letters rejected |
| Task07 | Type conversion surprises, float alternative | `gcc conversions.c -o t && ./t` | 5 surprises explained; float error grows with n |
| Task08 | Compilation stages, errors, warnings, split build | see `output.txt` | all stages and error classes captured |
| Task09 | Full program and test table | `gcc test09.c billing.c -o t && ./t` | 21 passed, 0 failed |
| Task10 | float vs paise vs int/long/long long totals | `gcc compare.c billing.c -o t && ./t` | int overflows at 60,000 bills; long long exact |
| Task11 | Final recommendation, tariff-from-file cost | `gcc config_read.c -o t && ./t` | 1.28 microseconds to read 6 tariff values |
| Task12 | Smart meter + time-of-day tariff + tariff file | `gcc smart_billing.c -o t && ./t tariff.cfg` | verified against an independent Python calculation |
