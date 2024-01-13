#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"

typedef struct {
    int r;
    int c;
} Point;

int det(Point p1, Point p2){
    return p1.c * p2.r - p1.r * p2.c;
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
}
