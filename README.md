 # CS 3503 Assignment 2- Data Representation and Mapping

 ## Author
 Jack Cundiff

 ## Description 
 Advanced data representation functions for Owl Tech’s CPU design team.
 ## Overview
This project implements:
- `oct_to_bin(const char *oct, char *out)` – Octal → Binary (3 bits per oct digit).
- `oct_to_hex(const char *oct, char *out)` – Octal → Hex (via binary regrouping into 4-bit nibbles).
- `hex_to_bin(const char *hex, char *out)` – Hex → Binary (4 bits per hex digit, case-insensitive).
- `to_sign_magnitude(int32_t n, char *out)` – 32-bit sign-magnitude representation.
- `to_ones_complement(int32_t n, char *out)` – 32-bit one’s complement.
- `to_twos_complement(int32_t n, char *out)` – 32-bit two’s complement (native C representation).

All outputs are null-terminated strings. For 32-bit outputs, buffers are length 33 (`32 bits + '\0'`).

## Files
- `convert.h` – function prototypes.
- `convert.c` – function implementations and helpers.
- `main.c` – test runner that reads `a2_test.txt` and prints `[PASS]/[FAIL]`.
- `a2_test.txt` – instructor-provided tests.
- `output.txt` – results produced by running the tests.

  ## What’s New
  - Direct mapping functions (oct/hex/bin)
  -  Signed number representations
  -  Reused test framework from A1
     
   ## Build Instructions
 Requires GCC/Clang. Example (Windows MinGW-w64 / macOS / Linux):
```bash
gcc -std=c11 -Wall -Wextra -O2 -o convert main.c convert.c

 ## Test Results
Test 1: oct_to_bin("725") -> Expected: "111010101", Got: "111010101" [PASS]
Test 2: oct_to_hex("345") -> Expected: "E5", Got: "E5" [PASS]
Test 3: hex_to_bin("a3") -> Expected: "10100011", Got: "10100011" [PASS]
...
Summary: XX/XX tests passed
(See full log in output.txt)
 
 
