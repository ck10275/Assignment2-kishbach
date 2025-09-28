#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include "convert.h"  // Contains your 6 function declarations

#define MAX_LINE_LEN 256
#define MAX_OUT_LEN 128

int main() {
    FILE *file = fopen("a2_test.txt", "r");
    if (!file) {
        perror("Failed to open test file");
        return 1;
    }

    char line[MAX_LINE_LEN];
    char func[32], input1[100], input2[100], expected[MAX_OUT_LEN], actual[MAX_OUT_LEN];
    int test_num = 1;
    int passed = 0, total = 0;

    while (fgets(line, sizeof(line), file)) {
        // Skip comments or empty lines
        if (line[0] == '#' || line[0] == '\n') continue;

        int fields = sscanf(line, "%31s %99s %99s", func, input1, input2);
        actual[0] = '\0';

        if (fields == 3) {
            strcpy(expected, input2);
        } else if (fields == 2) {
            strcpy(expected, "");
        } else {
            continue; // Skip malformed line
        }

        // Dispatch functions
        if (strcmp(func, "oct_to_bin") == 0) {
            oct_to_bin(input1, actual);
            printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   test_num, func, input1, expected, actual,
                   strcmp(actual, expected) == 0 ? "PASS" : "FAIL");

        } else if (strcmp(func, "oct_to_hex") == 0) {
            oct_to_hex(input1, actual);
            printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   test_num, func, input1, expected, actual,
                   strcmp(actual, expected) == 0 ? "PASS" : "FAIL");

        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(input1, actual);
            printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   test_num, func, input1, expected, actual,
                   strcmp(actual, expected) == 0 ? "PASS" : "FAIL");

        } else if (strcmp(func, "to_sign_magnitude") == 0) {
            int32_t val = atoi(input1);
            to_sign_magnitude(val, actual);
            printf("Test %d: %s(%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   test_num, func, val, expected, actual,
                   strcmp(actual, expected) == 0 ? "PASS" : "FAIL");

        } else if (strcmp(func, "to_ones_complement") == 0) {
            int32_t val = atoi(input1);
            to_ones_complement(val, actual);
            printf("Test %d: %s(%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   test_num, func, val, expected, actual,
                   strcmp(actual, expected) == 0 ? "PASS" : "FAIL");

        } else if (strcmp(func, "to_twos_complement") == 0) {
            int32_t val = atoi(input1);
            to_twos_complement(val, actual);
            printf("Test %d: %s(%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   test_num, func, val, expected, actual,
                   strcmp(actual, expected) == 0 ? "PASS" : "FAIL");

        } else {
            printf("Test %d: Unknown function \"%s\". Skipping.\n", test_num, func);
            test_num++;
            continue;
        }

        if (strcmp(actual, expected) == 0) {
            passed++;
        }

        total++;
        test_num++;
    }

    fclose(file);

    printf("\nSummary: %d/%d tests passed\n", passed, total);
    return 0;
}
