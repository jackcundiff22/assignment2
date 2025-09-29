#include "convert.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


static void to_32bit_binary(uint32_t value, char *out) {
    for (int i = 31; i >= 0; --i) {
        out[31 - i] = ((value >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}


static int hex_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    c = (char)toupper((unsigned char)c);
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
}


static char to_hex_digit(unsigned v) {
    return (v < 10) ? (char)('0' + v) : (char)('A' + (v - 10));
}


static void strip_leading_zeros_bin(const char *in, char *out) {
    const char *p = in;
    while (*p == '0') ++p;
    if (*p == '\0') { out[0] = '0'; out[1] = '\0'; return; }
    strcpy(out, p);
}


static void left_pad_to_nibble(const char *bin, char *padded) {
    size_t n = strlen(bin);
    size_t rem = n % 4;
    size_t pad = (rem == 0) ? 0 : 4 - rem;
    size_t i = 0;
    for (; i < pad; ++i) padded[i] = '0';
    strcpy(padded + i, bin);
}


static unsigned nibble_val(const char *four) {
    return (unsigned)((four[0]-'0')*8 + (four[1]-'0')*4 + (four[2]-'0')*2 + (four[3]-'0'));
}


void oct_to_bin(const char *oct, char *out) {
    
    if (oct[0] == '0' && oct[1] == '\0') { out[0] = '0'; out[1] = '\0'; return; }

    size_t pos = 0;
    for (size_t i = 0; oct[i]; ++i) {
        int d = oct[i] - '0';              
        out[pos++] = (char)(((d >> 2) & 1) ? '1' : '0');
        out[pos++] = (char)(((d >> 1) & 1) ? '1' : '0');
        out[pos++] = (char)(((d >> 0) & 1) ? '1' : '0');
    }
    out[pos] = '\0';
}


void hex_to_bin(const char *hex, char *out) {
    size_t pos = 0;
    for (size_t i = 0; hex[i]; ++i) {
        int v = hex_val(hex[i]);           
        out[pos++] = (char)(((v >> 3) & 1) ? '1' : '0');
        out[pos++] = (char)(((v >> 2) & 1) ? '1' : '0');
        out[pos++] = (char)(((v >> 1) & 1) ? '1' : '0');
        out[pos++] = (char)(((v >> 0) & 1) ? '1' : '0');
    }
    out[pos] = '\0';
}


void oct_to_hex(const char *oct, char *out) {
    char bin[256], bin_trim[256], pad[256];
    oct_to_bin(oct, bin);                  
    if (bin[0] == '0' && bin[1] == '\0') { 
        out[0] = '0'; out[1] = '\0'; return;
    }
    strip_leading_zeros_bin(bin, bin_trim);   
    left_pad_to_nibble(bin_trim, pad);        

    size_t n = strlen(pad);
    size_t pos = 0;
    for (size_t i = 0; i < n; i += 4) {
        unsigned v = nibble_val(&pad[i]);
        out[pos++] = to_hex_digit(v);         
    }
    out[pos] = '\0';
}




void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) { to_32bit_binary((uint32_t)n, out); return; }

    
    int64_t nn = n;
    uint32_t mag = (uint32_t)(-nn); 
    out[0] = '1';                     
    for (int i = 30; i >= 0; --i) {
        out[31 - i] = (char)(((mag >> i) & 1u) ? '1' : '0'); 
    }
    out[32] = '\0';
}


void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) { to_32bit_binary((uint32_t)n, out); return; }

    char posbits[33];
    to_32bit_binary((uint32_t)(- (int64_t)n), posbits); 
    for (int i = 0; i < 32; ++i) out[i] = (posbits[i] == '0') ? '1' : '0';
    out[32] = '\0';
}


void to_twos_complement(int32_t n, char *out) {
    to_32bit_binary((uint32_t)n, out);
}