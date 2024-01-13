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

int ****create_visited_array(int ROWS, int COLS) {
        int ****visited = malloc(ROWS * sizeof(int***));
        for(int i = 0; i < ROWS; i++) {
                visited[i] = malloc(COLS * sizeof(int**));
                for(int j = 0; j < COLS; j++) {
                        visited[i][j] = malloc(4 * sizeof(int*));
                        for(int k = 0; k < 4; k++) {
                                visited[i][j][k] = calloc(10, sizeof(int)); 
                        }
                }
        }
        return visited;
}

size_t min_path(char **grid, int ROWS, int COLS){
        int ****visited = create_visited_array(ROWS, COLS);
        Node **q = malloc(ROWS*COLS*4*10*sizeof(Node*));
        int q_size = 0;

        q[q_size++] = new_node(0,1,grid[0][1] - '0',0,1);
        q[q_size++] = new_node(1,0,grid[1][0] - '0',3,1);
        int count = 0;
        while (q_size > 0) {
                qsort(q, q_size, sizeof(Node*), compare_node_weights); // Not optimal, sort at every iteration, use heap instead?       
                Node* node = q[--q_size]; // access min element

                if (node->r < 0 || node->r >= ROWS || node->c < 0 || node->c >= COLS || visited[node->r][node->c][node->dir][node->dir_count-1]) {
                        continue;
                }
                visited[node->r][node->c][node->dir][node->dir_count-1] = 1;
                count++;
                if (count % 100000 == 0) printf("unique nodes: %d\n", count);
                if (node->r == ROWS-1 && node->c == COLS-1 && node->dir_count >=4) {
                        return node->w;
                }

                int next_dirs[4] = {1, 1, 1, 1}; //  0: right, 1: left, 2: up, 3: down
                if (node->dir_count == 10) {
                        next_dirs[node->dir] = 0;
                }
                if (node->dir_count < 4){
                        for (int i = 0; i < 4; i++) if (i != node->dir) next_dirs[i] = 0;
                }
                if (node->dir == 0) next_dirs[1] = 0;
                if (node->dir == 1) next_dirs[0] = 0;
                if (node->dir == 2) next_dirs[3] = 0;
                if (node->dir == 3) next_dirs[2] = 0;

                int next_dir_count;
                int next_w;
                if (next_dirs[0] && node->c + 1 < COLS){
                        if (0 == node->dir) next_dir_count = node->dir_count + 1;
                        else next_dir_count = 1;
                        int next_w = node->w + (grid[node->r][node->c + 1] - '0');
                        q[q_size++] = new_node(node->r, node->c+1, next_w, 0, next_dir_count);
                }
                if (next_dirs[1] && node->c - 1 >= 0){
                        if (1 == node->dir) next_dir_count = node->dir_count + 1;
                        else next_dir_count = 1;
                        next_w = node->w + (grid[node->r][node->c - 1] - '0');
                        q[q_size++] = new_node(node->r, node->c-1, next_w, 1, next_dir_count);
                }
                if (next_dirs[2] && node->r - 1 >= 0){
                        if (2 == node->dir) next_dir_count = node->dir_count + 1;
                        else next_dir_count = 1;
                        next_w = node->w + (grid[node->r - 1][node->c] - '0');
                        q[q_size++] = new_node(node->r-1, node->c, next_w, 2, next_dir_count);
                }
                if (next_dirs[3] && node->r + 1 < ROWS){
                        if (3 == node->dir) next_dir_count = node->dir_count + 1;
                        else next_dir_count = 1;
                        next_w = node->w + (grid[node->r + 1][node->c] - '0');
                        q[q_size++] = new_node(node->r+1, node->c, next_w, 3, next_dir_count);
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

    size_t result = min_path(grid, ROWS, COLS);
    printf("part1 result: %zu\n", result);

}



// Lesson: Can do pre-increment as well as post-increment
