#ifndef CONVERT_H
#define CONVERT_H

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int n, char *out);
void to_ones_complement(int n, char *out);
void to_twos_complement(int n, char *out);

#endif
