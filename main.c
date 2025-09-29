#include "convert.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

static void trim(char *s) {
    size_t n = strlen(s);
    while (n && (s[n-1]=='\n' || s[n-1]=='\r' || isspace((unsigned char)s[n-1]))) s[--n] = '\0';
    size_t i = 0;
    while (s[i] && isspace((unsigned char)s[i])) ++i;
    if (i) memmove(s, s+i, n - i + 1);
}

static int is_comment_or_blank(const char *s) {
    while (*s && isspace((unsigned char)*s)) ++s;
    return (*s=='\0' || *s=='#');
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s a2_test.txt\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("open test file"); return 1; }

    char line[512];
    unsigned testno = 0, passed = 0, total = 0;

    while (fgets(line, sizeof line, f)) {
        trim(line);
        if (is_comment_or_blank(line)) continue;

        char func[64], in[128], exp[256];
        int nt = sscanf(line, "%63s %127s %255s", func, in, exp);
        if (nt != 3) continue;

        ++testno; ++total;

        char got[512];
        if (strcmp(func, "oct_to_bin") == 0) {
            oct_to_bin(in, got);
        } else if (strcmp(func, "oct_to_hex") == 0) {
            oct_to_hex(in, got);
        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(in, got);
        } else if (strcmp(func, "to_sign_magnitude") == 0) {
            int32_t n = (int32_t)strtol(in, NULL, 10);
            to_sign_magnitude(n, got);
        } else if (strcmp(func, "to_ones_complement") == 0) {
            int32_t n = (int32_t)strtol(in, NULL, 10);
            to_ones_complement(n, got);
        } else if (strcmp(func, "to_twos_complement") == 0) {
            int32_t n = (int32_t)strtol(in, NULL, 10);
            to_twos_complement(n, got);
        } else {
            printf("Test %u: %s(%s) -> Unknown function name\n", testno, func, in);
            continue;
        }

        int ok = (strcmp(got, exp) == 0);
        if (ok) ++passed;

        // Match the PDF’s sample format for clarity. :contentReference[oaicite:21]{index=21}
        if (strncmp(func,"to_",3)==0) {
            printf("Test %u: %s(%s) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   testno, func, in, exp, got, ok?"PASS":"FAIL");
        } else {
            printf("Test %u: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   testno, func, in, exp, got, ok?"PASS":"FAIL");
        }
    }

    fclose(f);
    printf("Summary: %u/%u tests passed\n", passed, total);
    return 0;
}