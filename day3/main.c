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
                Point neighbour1 = {r-1, c};
                if (r > 0 && grid[r-1][c] == '*' )
                {
                    hmput(curNumStarNeighboursSet, neighbour1, 1);
                }
                Point neighbour2 = {r+1, c};
                if (r<ROWS-2 && grid[r+1][c] == '*')
                {
                    hmput(curNumStarNeighboursSet, neighbour2, 1);
                }
                Point neighbour3 = {r, c-1};
                if (c>0 && grid[r][c-1] == '*')
                {
                    hmput(curNumStarNeighboursSet, neighbour3, 1);
                }
                Point neighbour4 = {r, c+1};
                if (c < COLS-2 && grid[r][c+1] == '*')
                {
                    hmput(curNumStarNeighboursSet, neighbour4, 1);
                }
                Point neighbour5 = {r-1, c-1};
                if (r>0 && c > 0 && grid[r-1][c-1] == '*')
                {
                    hmput(curNumStarNeighboursSet, neighbour5, 1);
                }
                Point neighbour6 = {r-1, c+1};
                if (r>0 && c < COLS-2 && grid[r-1][c+1] == '*')
                {
                    hmput(curNumStarNeighboursSet, neighbour6, 1);
                }
                Point neighbour7 = {r+1, c-1};
                if (r<ROWS-2 && c > 0 && grid[r+1][c-1] == '*')
                {
                    hmput(curNumStarNeighboursSet, neighbour7, 1);
                }
                Point neighbour8 = {r+1, c+1};
                if (r<ROWS-2 && c<COLS-2 && grid[r+1][c+1] == '*')
                {
                    hmput(curNumStarNeighboursSet, neighbour8, 1);
                }
            }
            else
            {
                for(int i=0; i<hmlen(curNumStarNeighboursSet); i++)
                {
                    Point star_coordinates = curNumStarNeighboursSet[i].key;
                    Star star_info = hmget(starToInfo, star_coordinates);
                    star_info.neighbourProduct *= curNum;
                    star_info.neighbourCount += 1;
                    hmput(starToInfo, star_coordinates, star_info);
                }
                hmfree(curNumStarNeighboursSet);
                curNum = 0;
            }
            
        }
        for(int i=0; i<hmlen(curNumStarNeighboursSet); i++)
        {
            Point star_coordinates = curNumStarNeighboursSet[i].key;
            Star star_info = hmget(starToInfo, star_coordinates);
            star_info.neighbourProduct *= curNum;
            star_info.neighbourCount += 1;
            hmput(starToInfo, star_coordinates, star_info);
        }
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
    printf("total stars checked: %i\n", total_stars);
    printf("total gears found: %i\n", total_gears);
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