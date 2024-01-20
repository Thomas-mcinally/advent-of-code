#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"



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


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);

    Brick *bricks = malloc(sizeof(Brick)*linecount);

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
    }


}


// Pseudocode


//build out grid
// x_max, y_max = 0, 0, 0
// for brick in bricks:
//     x_max = max(x_max, brick.x_end)
//     y_max = max(y_max, brick.y_end)

// int grid[x_max][y_max] = {0};

// bricks.order(z_start)

//determine end coordinates for each brick
// for brick in bricks:
//     brick_z_width = brick.z_end - brick.z_start

//     resting_z = 0
//     for x in range(brick.x_start, brick.x_end):
//          for y in range(brick.y_start, brick.y_end):
//              resting_z = max(resting_z, grid[x][y])

//     for x in range(brick.x_start, brick.x_end):
//          for y in range(brick.y_start, brick.y_end):
//              grid[x][y] = resting_z + brick_z_width
//
//     brick.z_start = resting_z + 1
//     brick.z_end = resting_z + brick_z_width

//     z_start_to_bricks_map[brick.z_start].append(brick)



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
