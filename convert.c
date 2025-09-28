#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Helper: Convert integer to 32-bit binary string
void int_to_bin_str(unsigned int num, char *out) {
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (num & (1U << i)) ? '1' : '0';
    }
    out[32] = '\0';
}

// ==========================
// 1. Octal to Binary (3-bit map)
// ==========================
void oct_to_bin(const char *oct, char *out) {
    char bin_map[8][4] = {
        "000", "001", "010", "011", "100", "101", "110", "111"
    };
    out[0] = '\0';
    for (int i = 0; oct[i] != '\0'; i++) {
        if (oct[i] < '0' || oct[i] > '7') continue; // ignore invalid
        strcat(out, bin_map[oct[i] - '0']);
    }
}

// ==========================
// 2. Octal to Hex (via Binary)
// ==========================
void oct_to_hex(const char *oct, char *out) {
    char bin[100] = {0};
    oct_to_bin(oct, bin);

    // Pad binary with leading zeros to make length multiple of 4
    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;

    char padded[100] = {0};
    for (int i = 0; i < pad; i++) {
        padded[i] = '0';
    }
    strcat(padded, bin);
    strcpy(bin, padded);
    len = strlen(bin);

    char hex_map[] = "0123456789ABCDEF";
    char raw_hex[100] = {0};

    for (int i = 0; i < len; i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = (val << 1) | (bin[i + j] - '0');
        }
        strncat(raw_hex, &hex_map[val], 1);
    }

    // Strip leading zeros from raw_hex
    int start = 0;
    while (raw_hex[start] == '0' && raw_hex[start + 1] != '\0') {
        start++;
    }
    strcpy(out, raw_hex + start);
}


// ==========================
// 3. Hex to Binary (4-bit map)
// ==========================
void hex_to_bin(const char *hex, char *out) {
    char bin_map[16][5] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };
    out[0] = '\0';

    for (int i = 0; hex[i] != '\0'; i++) {
        char c = toupper(hex[i]);
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
        else continue; // skip invalid chars

        strcat(out, bin_map[val]);
    }
}

// ==========================
// 4. Sign Magnitude
// ==========================
void to_sign_magnitude(int n, char *out) {
    unsigned int mag = n < 0 ? -n : n;
    int_to_bin_str(mag, out);

    if (n < 0) {
        out[0] = '1'; // set sign bit
    } else {
        out[0] = '0'; // clear sign bit
    }
}

// ==========================
// 5. One's Complement
// ==========================
void to_ones_complement(int n, char *out) {
    if (n >= 0) {
        int_to_bin_str(n, out);
    } else {
        unsigned int mag = -n;
        char temp[33];
        int_to_bin_str(mag, temp);

        // Flip all bits
        for (int i = 0; i < 32; i++) {
            out[i] = temp[i] == '0' ? '1' : '0';
        }
        out[32] = '\0';
    }
}

// ==========================
// 6. Two's Complement
// ==========================
void to_twos_complement(int n, char *out) {
    unsigned int val = (unsigned int)n; // this handles two's complement naturally
    int_to_bin_str(val, out);
}

