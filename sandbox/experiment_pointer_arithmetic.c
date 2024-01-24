#include <stdio.h>

int main() {
    int x = 42;
    int *a = &x;

    // a points to an integer (4 bytes on many systems)
    printf("Original address: %p\n", (void*)a);

    // Incrementing the pointer by 1 moves to the next integer in memory
    int *b = a + 1;

    // b points to the next integer, which is 4 bytes away
    printf("New address: %p\n", (void*)b);

    return 0;
}

// Output:
// Original address: 0x16b8e2c18
// New address: 0x16b8e2c1c

// Explanation: 0x16b8e2c1c - 0x16b8e2c18 = 0x4 = 4 bytes = 1 integer