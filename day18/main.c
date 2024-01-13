#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "aoc_lib.h"

typedef struct {
    size_t r;
    size_t c;
} Point;

size_t det(Point p1, Point p2){
    return p1.c * p2.r - p1.r * p2.c;
}

size_t hex_val(char *hex){
    size_t val = 0;
    for (int i=0; i<5; i++){
        val *= 16;
        if (isdigit(hex[i])) val += hex[i] - '0';
        else val += hex[i] - 'a' + 10;
    }
    return val;
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);

    Point *points = malloc((linecount + 1) * sizeof(Point));
    Point start = {0, 0};
    points[0] = start;
    int edge_count = 0;
    for (int i = 0; i < linecount; i++)
    {
        char dir = lines[i][0];
        int val = extract_number_from_string(lines[i] + 2);
        edge_count += val;
        points[i+1] = points[i];

        switch(dir){
            case 'R':
                points[i+1].c += val;
                break;
            case 'L':
                points[i+1].c -= val;
                break;
            case 'U':
                points[i+1].r -= val;
                break;
            case 'D':
                points[i+1].r += val;
                break;
        }
    }


    int shoestring_area = 0;
    for (int i=0; i < linecount; i++) shoestring_area += det(points[i], points[i+1]);


    printf("part1 solution: %d\n", shoestring_area/2 + edge_count/2 + 1);


    Point *points2 = malloc((linecount + 1) * sizeof(Point));
    points2[0] = start;
    size_t edge_count2 = 0;
    for (int i=0; i<linecount; i++){
        char *hex_start = strchr(lines[i], '#');
        size_t val = hex_val(hex_start + 1);
        char dir2 = *(hex_start + 6);
        edge_count2 += val;
        points2[i+1] = points2[i];
        
        switch(dir2){
            case '0':
                points2[i+1].c += val;
                break;
            case '2':
                points2[i+1].c -= val;
                break;
            case '3':
                points2[i+1].r -= val;
                break;
            case '1':
                points2[i+1].r += val;
                break;
        }
    }

    size_t shoestring_area2 = 0;
    for (int i=0; i < linecount; i++) shoestring_area2 += det(points2[i], points2[i+1]);

    printf("part2 solution: %zu\n", shoestring_area2/2 + edge_count2/2 + 1);
}