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

typedef struct {
    Brick key;
    Brick **value;
} Brick_To_Bricks_Map;

typedef struct {
    Brick key;
    int value;
} Brick_To_Support_Count_Map;


int x_coordinates_overlap(Brick *brick1, Brick *brick2){
    if (brick1->x_start > brick2->x_start) return x_coordinates_overlap(brick2, brick1);
    return brick1->x_end >= brick2->x_start;
}

int y_coordinates_overlap(Brick *brick1, Brick *brick2){
    if (brick1->y_start > brick2->y_start) return y_coordinates_overlap(brick2, brick1);
    return brick1->y_end >= brick2->y_start;
}

int compare_brick_z_start(const void *a, const void *b) {
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
        int x1, y1, z1, x2, y2, z2;
        sscanf(line, "%d,%d,%d", &x1, &y1, &z1);
        sscanf(separator+1, "%d,%d,%d", &x2, &y2, &z2);

        bricks[i].x_start = min(x1, x2);
        bricks[i].y_start = min(y1, y2);
        bricks[i].z_start = min(z1, z2);
        bricks[i].x_end = max(x1, x2);
        bricks[i].y_end = max(y1, y2);
        bricks[i].z_end = max(z1, z2);

        highest_x = max(highest_x, bricks[i].x_end);
        highest_y = max(highest_y, bricks[i].y_end);
        highest_z = max(highest_z, bricks[i].z_end);
    }

    qsort(bricks, linecount, sizeof(Brick), compare_brick_z_start);

    // find and update z_coordinates for each brick to reflect end position
    int **grid = malloc(sizeof(int *)*(highest_x + 1));
    for(int i=0; i<highest_x+1; i++) grid[i] = calloc(highest_y+1, sizeof(int));

    Brick ***z_start_buckets = NULL;
    arrsetlen(z_start_buckets, highest_z+1);
    for(int i=0; i<highest_z+1; i++) z_start_buckets[i] = NULL;
    for (int i=0; i<linecount; i++){
        Brick *brick = &bricks[i];
        int brick_z_width = brick->z_end - brick->z_start + 1;
        int ground_level = 0;
        for (int x=brick->x_start; x<brick->x_end+1; x++){
            for (int y=brick->y_start; y<brick->y_end+1; y++){
                ground_level = max(ground_level, grid[x][y]);
            }
        }
        for (int x = brick->x_start; x < brick->x_end+1; x++){
            for (int y = brick->y_start; y < brick->y_end+1; y++){
                grid[x][y] = ground_level + brick_z_width;
            }
        }

        brick->z_start = ground_level + 1;
        brick->z_end = ground_level + brick_z_width;
        arrput(z_start_buckets[brick->z_start], brick);
    }

    Brick_To_Bricks_Map *brick_to_supported_bricks_map = NULL;
    Brick_To_Support_Count_Map *brick_to_support_count_map = NULL;
    //build brick_to_supported_bricks_map and brick_to_support_count_map

    for(int cur_z=0; cur_z<arrlen(z_start_buckets); cur_z++){
        for (int i=0; i<arrlen(z_start_buckets[cur_z]); i++){
            Brick *bottom_brick = z_start_buckets[cur_z][i];
            for (int j=0; j<arrlen(z_start_buckets[bottom_brick->z_end+1]); j++){
                Brick *top_brick = z_start_buckets[bottom_brick->z_end+1][j];
                if (x_coordinates_overlap(bottom_brick, top_brick) && y_coordinates_overlap(bottom_brick, top_brick)){
                    //update brick_to_support_count
                    if (hmgeti(brick_to_support_count_map, *top_brick) == -1){
                        hmput(brick_to_support_count_map, *top_brick, 1);
                    }
                    else{
                        int support_count = hmget(brick_to_support_count_map, *top_brick);
                        hmput(brick_to_support_count_map, *top_brick, support_count+1);
                    }
                    //update brick_to_supported_bricks_map
                    if (hmgeti(brick_to_supported_bricks_map, *bottom_brick) == -1){
                        Brick **supported_bricks = NULL;
                        arrput(supported_bricks, top_brick);
                        hmput(brick_to_supported_bricks_map, *bottom_brick, supported_bricks);
                    }
                    else{
                        Brick **supported_bricks = hmget(brick_to_supported_bricks_map, *bottom_brick);
                        arrput(supported_bricks, top_brick);
                        hmput(brick_to_supported_bricks_map, *bottom_brick, supported_bricks);
                    }
                }
            }
        }
    }

    size_t safe_to_disintegrate_count = 0;
    for (int i=0; i<linecount; i++){
        Brick *brick = &bricks[i];
        if (hmgeti(brick_to_supported_bricks_map, *brick) == -1){
            safe_to_disintegrate_count++;
            continue;
        };
        int safe_to_disintegrate = 1;
        Brick **supported_bricks = hmget(brick_to_supported_bricks_map, *brick);
        for (int j=0; j<arrlen(supported_bricks); j++){
            Brick *supported_brick = supported_bricks[j];
            int support_count = hmget(brick_to_support_count_map, *supported_brick);
            if (support_count == 1){
                safe_to_disintegrate = 0;
                break;
            }
        }
        if(safe_to_disintegrate) safe_to_disintegrate_count++;
        
    }
    printf("part1 solution: %zu\n", safe_to_disintegrate_count);


    size_t part2_count = 0;
    for (int i=0; i<linecount; i++){
        Brick_To_Support_Count_Map *brick_to_support_count_map_copy = NULL;
        for (int j=0; j<hmlen(brick_to_support_count_map); j++){
            Brick brick = brick_to_support_count_map[j].key;
            int support_count = brick_to_support_count_map[j].value;
            hmput(brick_to_support_count_map_copy, brick, support_count);
        }

        Brick *brick_to_disintegrate = &bricks[i];

        //bfs to find all bricks that will fall
        Brick **queue = NULL;
        arrput(queue, brick_to_disintegrate);
        while (arrlen(queue)>0){
            Brick *cur = queue[0];
            arrdel(queue, 0);

            Brick **supported_bricks = hmget(brick_to_supported_bricks_map, *cur);
            for (int j=0; j<arrlen(supported_bricks); j++){
                Brick *supported_brick = supported_bricks[j];
                int support_count = hmget(brick_to_support_count_map_copy, *supported_brick);
                if (support_count == 1){
                    arrput(queue, supported_brick);
                    part2_count++;
                }
                else {
                    hmput(brick_to_support_count_map_copy, *supported_brick, support_count-1);
                }
            }
        }  
    }

    printf("part2 solution: %zu\n", part2_count);

    return 0;
}
