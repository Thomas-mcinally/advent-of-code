#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include <stdio.h>


typedef struct {
    int arr[10];
} Node;
typedef struct {
    int x;
    int y;
} Coordinates;

typedef struct {
    int key;
    int value;
} Map_Element;

typedef struct {
    Coordinates key;
    int value;
} Map_Element_Struct_Keys;

typedef struct {
    int key;
    Node value;
} Map_Element_Struct_Values;

typedef struct {
    int key;
    int (*value)[3];
} Map_Element_Arr_Values;



int main() {
    // Test hashmap
    printf("Testing hashmap\n");
    Map_Element *map = NULL;
    hmput(map, 0, 100);
    printf("value of key 0: %u\n", hmget(map, 0));
    hmfree(map);

    //Test hashmap with default values
    printf("Testing hashmap with default values\n");
    Map_Element *map_default = NULL;
    hmput(map_default, 1, 100);
    hmdefault(map_default, 1337);
    printf("value of key 1: %d\n", hmget(map_default, 1));
    printf("value of key 2: %d\n", hmget(map_default, 2));

    //Test hashmap with struct keys
    printf("Testing hashmap with struct keys\n");
    Map_Element_Struct_Keys *map_struct_keys = NULL;
    Coordinates key1 = {1, 100};
    Coordinates key2 = {2, 200};
    hmput(map_struct_keys, key1, 1);
    hmput(map_struct_keys, key2, 2);
    printf("map[key1]: %d\n", hmget(map_struct_keys, key1));
    printf("map[key2]: %d\n", hmget(map_struct_keys, key2));

    // Test hashmap with struct values
    printf("Testing hashmap with struct values\n");
    Map_Element_Struct_Values *map_struct_values = NULL;
    Node value1 = {{0,0,0,0,0,0,0,0,0,0}};
    hmput(map_struct_values, 1, value1);
    hmget(map_struct_values, 1).arr[0] = 100;
    printf("first val of map[1]: %d\n", hmget(map_struct_values, 1).arr[0]); //expect 100

    // Test hashmap with arr values
    printf("Testing hashmap with arr values\n");
    Map_Element_Arr_Values *map_arr_values = NULL;
    int value2[3] = {0,2,4};
    int (*ptr_arr)[3] = &value2;
    printf("ptr_arr[0]: %d\n", (*ptr_arr)[0]); // expect 0
    printf("ptr_arr[1]: %d\n", (*ptr_arr)[1]); // expect 2
    printf("ptr_arr[2]: %d\n", (*ptr_arr)[2]); // expect 4
    printf("arr[0]: %d\n", value2[0]); // expect 0
    printf("arr[1]: %d\n", value2[1]); // expect 2
    printf("arr[2]: %d\n", value2[2]); // expect 4

    hmput(map_arr_values, 1, &value2);
    printf("first val of map[1] before change: %d\n", (*hmget(map_arr_values, 1))[0]); //expect 0
    (*hmget(map_arr_values, 1))[0] = 100;
    printf("first val of map[1] after change: %d\n", (*hmget(map_arr_values, 1))[0]); //expect 100

    // test dynamic array
    printf("Testing dynamic array\n");
    int *arr = NULL;
    arrput(arr, 1);
    arrput(arr, 2);
    arrput(arr, 3);
    printf("arr[0]: %d\n", arr[0]);
    printf("arr[1]: %d\n", arr[1]);
    printf("arr[2]: %d\n", arr[2]);
    arrfree(arr);

    // test dynamic array of structs
    printf("Testing dynamic array of structs\n");
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