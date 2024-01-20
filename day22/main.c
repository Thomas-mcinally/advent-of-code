#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"




typedef struct {
    int x_start;
    int y_start;
    int z_start;
    int x_end;
    int y_end;
    int z_end;
} Brick;

bool x_coordinates_overlap(Brick *brick1, Brick *brick2){
    if (brick1->x_start > brick2->x_start) return x_coordinates_overlap(brick2, brick1);
    return brick1->x_end > brick2->x_start;
}

bool y_coordinates_overlap(Brick *brick1, Brick *brick2){
    if (brick1->y_start > brick2->y_start) return y_coordinates_overlap(brick2, brick1);
    return brick1->y_end > brick2->y_start;
}

int compare(const void *a, const void *b) {
    const Brick *brickA = (const Brick *)a;
    const Brick *brickB = (const Brick *)b;

    return (brickA->z_start - brickB->z_start);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);

    Brick *bricks = malloc(sizeof(Brick)*linecount);
    int highest_x = 0;
    int highest_y = 0;
    int highest_z = 0;
    for(int i=0; i<linecount; i++){
        char *line = lines[i];
        char *separator = strchr(line, '~');
        *separator = '\0';
        char x1, y1, z1, x2, y2, z2;
        sscanf(line, "%c,%c,%c", &x1, &y1, &z1);
        sscanf(separator+1, "%c,%c,%c", &x2, &y2, &z2);

        bricks[i].x_start = min(x1-'0', x2-'0');
        bricks[i].y_start = min(y1-'0', y2-'0');
        bricks[i].z_start = min(z1-'0', z2-'0');
        bricks[i].x_end = max(x1-'0', x2-'0');
        bricks[i].y_end = max(y1-'0', y2-'0');
        bricks[i].z_end = max(z1-'0', z2-'0');

        highest_x = max(highest_x, bricks[i].x_end);
        highest_y = max(highest_y, bricks[i].y_end);
        highest_z = max(highest_z, bricks[i].z_end);
    }


    //use qsort to sort bricks based on z_start
    qsort(bricks, linecount, sizeof(Brick), compare);

    // find and update z_coordinates for each brick to reflect end position
    int **grid = malloc(sizeof(int *)*(highest_x + 1));
    for(int i=0; i<highest_x+1; i++) grid[i] = calloc(highest_y+1, sizeof(int));

    Brick ***z_start_buckets = calloc(highest_z+1, sizeof(Brick **));
    for(int i=0; i<highest_z+1; i++) z_start_buckets[i] = NULL;
    for (int i=0; i<linecount; i++){
        Brick *brick = &bricks[i];
        int brick_z_width = brick->z_end - brick->z_start + 1;
        int resting_z = 0;
        for (int x = brick->x_start; x < brick->x_end+1; x++){
            for (int y = brick->y_start; y < brick->y_end+1; y++){
                resting_z = max(resting_z, grid[x][y]);
            }
        }
        for (int x = brick->x_start; x < brick->x_end+1; x++){
            for (int y = brick->y_start; y < brick->y_end+1; y++){
                grid[x][y] = resting_z + brick_z_width;
            }
        }

        brick->z_start = resting_z + 1;
        brick->z_end = brick->z_start + brick_z_width - 1;
        arrput(z_start_buckets[brick->z_start], brick);
    }


    return 0;
}


// Pseudocode

//build brick_to_supported_bricks_map and brick_to_support_count_map
//cur_z = 0
// while cur_z in z_to_bricks_map:
//     for bottom_brick in z_to_bricks_map[cur_z]:
//         for top_brick in z_to_bricks_map[bottom_brick.end_z + 1]:
//             if (x_coordinates_overlap(bottom_brick, top_brick) || y_coordinates_overlap(bottom_brick, top_brick)) {
//                  brick_to_supported_bricks_map[bottom_brick].append(top_brick);
//                  brick_to_support_count_map[top_brick] += 1;
//                }
//     cur_z += 1;



// int safe_to_disintegrate_count = 0;
// for brick in bricks:
//     if (arrlen(brick_to_supported_bricks_map) == 0) {safe_to_disintegrate_count += 1;continue;}
//     bool safe_to_disintegrate = true;
//     for supported_brick in brick_to_supported_bricks_map[brick]:
//         if (brick_to_support_count_map[supported_brick] == 1) {safe_to_disintegrate = false; break;}
//     if (safe_to_disintegrate) {safe_to_disintegrate_count += 1;}

// return safe_to_disintegrate_count;



//expect 5