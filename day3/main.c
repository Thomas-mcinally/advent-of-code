#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_file_to_lines(char ***lines){
    int MAX_LINE_LENGTH = 256;
    FILE *file = fopen("./input.txt", "r");
    int lineCount = 0;

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        *lines = realloc(*lines, (lineCount + 1) * sizeof(char *));
        (*lines)[lineCount] = malloc(strlen(buffer) + 1);

        strcpy((*lines)[lineCount], buffer);
        lineCount++;
    }
    fclose(file);
    return lineCount;
}

int is_symbol(char c)
{
    if (isdigit(c) || c == '.') return 0;
    return 1;
}

int at_least_one_neighbour_is_symbol(char **lines, int i, int j, int max_i, int max_j)
{
    if (j > 0 && is_symbol(lines[i][j-1])) return 1;
    if (j < max_j && is_symbol(lines[i][j+1])) return 1;
    if (i > 0 && is_symbol(lines[i-1][j])) return 1;
    if (i < max_i && is_symbol(lines[i+1][j])) return 1;
    if (i > 0 && j > 0 && is_symbol(lines[i-1][j-1])) return 1;
    if (i > 0 && j < max_j && is_symbol(lines[i-1][j+1])) return 1;
    if (i < max_i && j > 0 && is_symbol(lines[i+1][j-1])) return 1;
    if (i < max_i && j < max_j && is_symbol(lines[i+1][j+1])) return 1;
    return 0;

}

int part1(char **grid, int ROWS, int COLS)
{
    if (ROWS != COLS)
    {
        printf("ERROR: ROWS != COLS\n");
        return 1;
    }

    int partNumberSum = 0;
    int curNum = 0;
    int curNumIsValid = 0;
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (isdigit(grid[r][c]))
            {
                curNum = curNum * 10 + (grid[r][c] - '0');
                if (at_least_one_neighbour_is_symbol(grid, r, c, ROWS-1, COLS-1))
                {
                    curNumIsValid = 1;
                }
            }
            else
            {
                if (curNumIsValid) partNumberSum += curNum;
                curNum = 0;
                curNumIsValid = 0;
            }
            
        }
        if (curNumIsValid) partNumberSum += curNum;
        curNum = 0;
        curNumIsValid = 0;
    }
    return partNumberSum;
}

int part2(char **grid, int ROWS, int COLS)
// HARD WITHOUT A HASHMAP TYPE
{
    if (ROWS != COLS)
    {
        printf("ERROR: ROWS != COLS\n");
        return 1;
    }

    int curNum = 0;
    // curNumStarNeighbours = [(x,y), (x,y), (x,y), (x,y)]
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (isdigit(grid[r][c]))
            {
                curNum = curNum * 10 + (grid[r][c] - '0');
                // Check if any neighbour is star and update curNumStarNeighbours
            }
            else
            {
                curNum = 0;
                // update star: neighbouring nums hashmap
            }
            
        }
        curNum = 0;
        // update star: neighbouring nums hashmap
    }
    // Calculate gearratioSum

    // return gearratioSum

}
int main()
{
    int partNumberSum = 0;
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines);

    printf("Part 1: %i\n", part1(lines, linecount, strlen(lines[0]) - 1));
    char myChar = 'a';
    myChar += 28;
    printf("%c\n", myChar);

}
