/* Alternative: read a whole line with fgets, convert with strtol */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(void)
{
    char line[64];
    printf("Enter previous reading: ");
    if (!fgets(line, sizeof line, stdin)) return 1;
    char *end;
    errno = 0;
    long v = strtol(line, &end, 10);
    if (end == line || (*end != '\n' && *end != '\0') || errno) {
        printf("Invalid input '%.10s' -- line discarded, program continues safely.\n", line);
        return 1;
    }
    printf("Parsed value = %ld\n", v);
    return 0;
}
