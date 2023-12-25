#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include <stdio.h>

typedef struct {
    int key;
    int value;
} Map_Element;

int main() {
    Map_Element *map = NULL;

    hmput(map, 0, 100);

    printf(" value of key 0: %u\n", hmget(map, 0));
};