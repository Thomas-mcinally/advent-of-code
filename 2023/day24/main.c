#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"

typedef struct {
    double px;
    double py;
    double pz;
    int vx;
    int vy;
    int vz;
} Hailstone;

typedef struct {
    double px;
    double py;
    double t1;
    double t2;
} Intersection;


int are_paths_paralell(Hailstone *a, Hailstone *b){
    double ratio1 = (double)a->vx/(double)b->vx;
    double ratio2 = (double)a->vy/(double)b->vy;
    return (ratio1 == ratio2); 
}

Intersection get_hailstone_path_intersection_point(Hailstone *a, Hailstone *b){
    // Non-paralell linear paths -> there will be one (and only one) intersection point (x,y). Can calculate this from start positions and velocities

    // x = x1 + t1*vx1 (1)
    // y = y1 + t1*vy1 (2)
    // x = x2 + t2*vx2 (3)
    // y = y2 + t2*vy2 (4)

    // (1) - (3)
    // 0 = x1-x2 + t1*vx1 - t2*vx2
    // (x2 - x1 + t2*vx2) / vx1 = t1 (5)

    // (2) - (4)
    // 0 = y1 - y2 + t1*vy1 - t2*vy2 (6)
    // t2 = (y1 - y2 + t1*vy1) / vy2 (7)

    // sub (5) into (6)
    // 0 = y1-y2 + ((x2 - x1 + t2*vx2) / vx1)*vy1 - t2*vy2
    // 0 = y1 - y2 + (x2*vy1 - x1*vy1 + t2*vx2*vy1) / vx1 - t2*vy2
    // 0 = vx1*y1 - vx1*y2 + x2*vy1 - x1*vy1 + t2*vx2*vy1 - t2*vx1*vy2
    // t2*vx1*vy2 - t2*vx2*vy1 = vx1*y1 - vx1*y2 + x2*vy1 - x1*vy1
    // t2 = (vx1*y1 - vx1*y2 + x2*vy1 - x1*vy1) / (vx1*vy2 - vx2*vy1) (8)

    // Use (8) to get val for t2
    // use (5) to get val for t1
    // use (3) to get val for x
    // use (4) to get val for y

    double intersection_t2 = (a->vx*a->py - a->vx*b->py + b->px*a->vy - a->px*a->vy) / (a->vx*b->vy - b->vx*a->vy);
    double intersection_t1 = (b->px - a->px + intersection_t2*b->vx) / a->vx;
    double intersection_x = b->px + intersection_t2*b->vx;
    double intersection_y = b->py + intersection_t2*b->vy;
    

    return (Intersection){.px = intersection_x, .py = intersection_y, .t1 = intersection_t1, .t2 = intersection_t2};
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);

    Hailstone **hailstones = malloc(sizeof(Hailstone*)*linecount);
    for(int i=0; i<linecount; i++){
        char *line = lines[i];
        char *separator = strchr(line, '@');
        *separator = '\0';
        double px, py, pz;
        int vx, vy, vz;
        sscanf(line, "%lf,%lf,%lf", &px, &py, &pz);
        sscanf(separator+1, "%d,%d,%d", &vx, &vy, &vz);

        Hailstone *hailstone = malloc(sizeof(Hailstone));
        hailstone->px = px;
        hailstone->py = py;
        hailstone->pz = pz;
        hailstone->vx = vx;
        hailstone->vy = vy;
        hailstone->vz = vz;
        hailstones[i] = hailstone;
    }

    size_t part1_count = 0;
    for (int i1=0; i1<linecount; i1++){
        for (int i2=i1+1; i2<linecount; i2++){
            Hailstone *hailstone1 = hailstones[i1];
            Hailstone *hailstone2 = hailstones[i2];
            if (are_paths_paralell(hailstone1, hailstone2))continue;

            Intersection intersection = get_hailstone_path_intersection_point(hailstone1, hailstone2);

            if (
                intersection.px >= 200000000000000 
                && intersection.py >= 200000000000000 
                && intersection.px <= 400000000000000 
                && intersection.py <= 400000000000000
                && intersection.t1 >= 0
                && intersection.t2 >= 0
            ){
                part1_count++;
            }


        }
    }
    printf("Part1 sol: %zu\n", part1_count);
}
