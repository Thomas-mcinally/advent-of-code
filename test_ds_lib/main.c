#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include <stdio.h>

typedef struct {
    int key;
    int value;
} Map_Element;

typedef struct {
    int x;
    int y;
} Coordinates;

int main() {
    // Test hashmap
    Map_Element *map = NULL;
    hmput(map, 0, 100);
    printf("value of key 0: %u\n", hmget(map, 0));
    hmfree(map);

    // test dynamic array
    int *arr = NULL;
    arrput(arr, 1);
    arrput(arr, 2);
    arrput(arr, 3);
    printf("arr[0]: %d\n", arr[0]);
    printf("arr[1]: %d\n", arr[1]);
    printf("arr[2]: %d\n", arr[2]);
    arrfree(arr);

    // test dynamic array of structs
    Coordinates *coords = NULL;
    Coordinates my_point = {1, 100};
    Coordinates my_point2 = {2, 200};
    arrput(coords, my_point);
    arrput(coords, my_point2);
    printf("coords[0].x: %d\n", coords[0].x);
    printf("coords[0].y: %d\n", coords[0].y);
    printf("coords[1].x: %d\n", coords[1].x);
    printf("coords[1].y: %d\n", coords[1].y);
    arrfree(coords);
};