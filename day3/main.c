#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    long long int neighbourProduct;
    int neighbourCount;
} Star;

typedef struct {
    Point key;
    Star value;
} Point_To_Star_Info_Map;

typedef struct {
    Point key;
    int value; //dummy value
} Point_Set;


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

void updateStarToInfo(Point_To_Star_Info_Map *starToInfo, Point_Set *numStarNeighboursSet, int num) {
    for (int i = 0; i < hmlen(numStarNeighboursSet); i++) {
        Point starCoordinates = numStarNeighboursSet[i].key;
        Star starInfo = hmget(starToInfo, starCoordinates);
        starInfo.neighbourProduct *= num;
        starInfo.neighbourCount += 1;
        hmput(starToInfo, starCoordinates, starInfo);
    }
}

int part1(char **grid, int ROWS, int COLS)
{
    if (ROWS != COLS)
    {
        printf("ERROR: ROWS != COLS, ROWS: %i, COLS: %i\n", ROWS, COLS);
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

long long int part2(char **grid, int ROWS, int COLS)
{
    if (ROWS != COLS)
    {
        printf("ERROR: ROWS != COLS, ROWS: %i, COLS: %i\n", ROWS, COLS);
        return 1;
    }

    Point_To_Star_Info_Map *starToInfo = NULL;    // (star_x, star_y): {neighbourProduct, neighbourCount}
    //find all stars
    for (int r=0; r<ROWS; r++)
    {
        for (int c=0; c<COLS; c++)
        {
            if (grid[r][c] == '*')
            {
                Point star_coordinates = {r, c};
                Star star_info = {1, 0};
                hmput(starToInfo, star_coordinates, star_info);
            }
        }
    }

    int curNum = 0;

    Point_Set *curNumStarNeighboursSet = NULL; // Set {(x,y), (x,y), (x,y), (x,y)}
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (isdigit(grid[r][c]))
            {
                curNum = curNum * 10 + (grid[r][c] - '0');
                // Check if any neighbour is star and update curNumStarNeighbours
                Point neighbours[] = {
                            {r - 1, c}, {r + 1, c},
                            {r, c - 1}, {r, c + 1},
                            {r - 1, c - 1}, {r - 1, c + 1},
                            {r + 1, c - 1}, {r + 1, c + 1}
                        };

                for (int i = 0; i < 8; i++) {
                    if (hmgeti(starToInfo, neighbours[i]) >= 0) {
                        hmput(curNumStarNeighboursSet, neighbours[i], 1);
                    }
                }
            }
            else
            {
                updateStarToInfo(starToInfo, curNumStarNeighboursSet, curNum);
                hmfree(curNumStarNeighboursSet);
                curNum = 0;
            }
            
        }
        updateStarToInfo(starToInfo, curNumStarNeighboursSet, curNum);
        hmfree(curNumStarNeighboursSet);
        curNum = 0;
    }

    long long int total_gear_ratio = 0;
    int total_stars = 0;
    int total_gears = 0;
    for (int i=0; i<hmlen(starToInfo); i++)
    {
        total_stars++;
        Star star_info = starToInfo[i].value;
        if (star_info.neighbourCount != 2) continue;
        total_gears++;
        total_gear_ratio += star_info.neighbourProduct;
    }

    hmfree(starToInfo);
    return total_gear_ratio;
}
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);

    printf("Part 1: %i\n", part1(lines, linecount-1, strlen(lines[0])));
    printf("Part 2: %lli\n", part2(lines, linecount-1, strlen(lines[0])));
    return 0;
}