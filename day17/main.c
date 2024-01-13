#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"


typedef struct {
    int r, c, w, dir, dir_count;
} Node;

Node* new_node(int r, int c, int w, int dir, int dir_count) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->r = r;
        node->c = c;
        node->w = w;
        node->dir = dir;
        node->dir_count = dir_count;
        return node;
}

int compare_node_weights(const void* a, const void* b) {
    Node* nodeA = *(Node**)a;
    Node* nodeB = *(Node**)b;
    if (nodeA->w < nodeB->w) {
        return 1;
    } else if (nodeA->w > nodeB->w) {
        return -1;
    } else {
        return 0;
    }
}

int ****create_visited_array(int ROWS, int COLS, int max_steps) {
        int ****visited = malloc(ROWS * sizeof(int***));
        for(int i = 0; i < ROWS; i++) {
                visited[i] = malloc(COLS * sizeof(int**));
                for(int j = 0; j < COLS; j++) {
                        visited[i][j] = malloc(4 * sizeof(int*));
                        for(int k = 0; k < 4; k++) {
                                visited[i][j][k] = calloc(max_steps, sizeof(int)); 
                        }
                }
        }
        return visited;
}

size_t min_path(char **grid, int ROWS, int COLS, int max_steps, int min_steps){
        int ****visited = create_visited_array(ROWS, COLS, max_steps);
        Node **q = malloc(ROWS*COLS*4*max_steps*sizeof(Node*));
        int q_size = 0;

        q[q_size++] = new_node(0,1,0,0,1);
        q[q_size++] = new_node(1,0,0,3,1);
        while (q_size > 0) {
                qsort(q, q_size, sizeof(Node*), compare_node_weights); // Not optimal, sort at every iteration, use heap instead?       
                Node* node = q[--q_size]; // access min element

                if (node->r < 0 || node->r >= ROWS || node->c < 0 || node->c >= COLS || visited[node->r][node->c][node->dir][node->dir_count-1]) {
                        continue;
                }
                int cur_w = node->w + (grid[node->r][node->c] - '0');
                if (node->r == ROWS-1 && node->c == COLS-1 && node->dir_count >=min_steps) {
                        return cur_w;
                }
                visited[node->r][node->c][node->dir][node->dir_count-1] = 1;

                int next_coords[4][2] = {{node->r, node->c+1}, {node->r, node->c-1}, {node->r-1, node->c}, {node->r+1, node->c}};
                int next_dirs[4] = {1, 1, 1, 1}; //  0: right, 1: left, 2: up, 3: down
                if (node->dir_count == max_steps) {
                        next_dirs[node->dir] = 0;
                }
                if (node->dir_count < min_steps){
                        for (int i = 0; i < 4; i++) if (i != node->dir) next_dirs[i] = 0;
                }
                if (node->dir == 0) next_dirs[1] = 0;
                if (node->dir == 1) next_dirs[0] = 0;
                if (node->dir == 2) next_dirs[3] = 0;
                if (node->dir == 3) next_dirs[2] = 0;


                
                int next_dir_count;
                for (int i=0; i<4; i++){
                        if (!next_dirs[i]) continue;
                        if (i == node->dir) next_dir_count = node->dir_count + 1;
                        else next_dir_count = 1;
                        
                        q[q_size++] = new_node(next_coords[i][0], next_coords[i][1], cur_w, i, next_dir_count);
                }
        }

        printf("NO SOLUTION FOUND\n");
        return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **grid = NULL;
    int ROWS = read_file_to_lines(&grid, file_path);
    int COLS = strlen(grid[0]);


    printf("part1 result: %zu\n", min_path(grid, ROWS, COLS, 3, 1));
    printf("part2 result: %zu\n", min_path(grid, ROWS, COLS, 10, 4));

}

