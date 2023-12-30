#include <string.h>
#include <stdio.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    char *key;
    char **value;
} Node_To_Neighbours;

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

    char *instructions = lines[0];
    int instruction_length = strlen(instructions);

    Node_To_Neighbours *adj = NULL;
    for (int i = 2; i < linecount-1; i++)
    {
        char *line = lines[i];
        line[3] = '\0';
        line[10] = '\0';
        line[15] = '\0';

        char **neighbours = malloc(2 * sizeof(char*));
        neighbours[0] = line + 7;
        neighbours[1] = line + 12;
        shput(adj, line, neighbours);
    }
    char **val = shget(adj, "AAA"); 
    printf("neighbours of AAA: %s, %s\n", val[0], val[1]);

    char *current_node = "AAA";
    int step_count = 0;
    int i = 0;
    while (strcmp(current_node, "ZZZ") != 0)
    {
        if (instructions[i] == 'L') current_node = shget(adj, current_node)[0];
        else current_node = shget(adj, current_node)[1];
        step_count++;
        i++;
        if (i == instruction_length) i = 0;
    }
    printf("Part1: %d\n", step_count);


    for (int i = 0; i < linecount; i++) free(lines[i]);
    free(lines);
    for (int i = 0; i < shlen(adj); i++) free(adj[i].value);
    hmfree(adj);

    return 0;
}


// Process inputs
    // First line -> char array "instructions"
    // All other lines -> graph adjacency list, i.e.  hashmap {node: [neighbourL, neighbourR]}

// Traverse graph using adjacency list and insturctions, until reach node ZZZ. Assume able to reach ZZZ.
