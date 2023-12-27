#include <stdio.h>
#include <stdint.h>

int main() {
    size_t max_size = SIZE_MAX;
    long long unsigned int max_llu = UINT64_MAX;
    long unsigned int max_lu = UINT32_MAX;
    unsigned int max_u = UINT32_MAX;

    printf("Maximum value of size_t: %zu\n", max_size); // 18446744073709551615, max 64-bit unsigned int
    printf("Maximum value of uint64: %llu\n", max_llu); // 18446744073709551615, max 64-bit unsigned int
    printf("Maximum value of uint32: %lu\n", max_lu); // 4294967295, max 32-bit unsigned int
    printf("Maximum value of uint: %u\n", max_u); // 4294967295, max 32-bit unsigned int


    return 0;
}
