#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct
{
    int x;
    int y;
} Point;

typedef struct
{
    long long int neighbourProduct;
    int neighbourCount;
} Star;

typedef struct
{
    Point key;
    Star value;
} Point_To_Star_Map;

typedef struct
{
    Point key;
    int value; // dummy value
} Point_Set;

int is_symbol(char c)
{
    if (isdigit(c) || c == '.')
        return 0;
    return 1;
}

int at_least_one_neighbour_is_symbol(char **lines, int i, int j, int max_i, int max_j)
{
    if (j > 0 && is_symbol(lines[i][j - 1]))
        return 1;
    if (j < max_j && is_symbol(lines[i][j + 1]))
        return 1;
    if (i > 0 && is_symbol(lines[i - 1][j]))
        return 1;
    if (i < max_i && is_symbol(lines[i + 1][j]))
        return 1;
    if (i > 0 && j > 0 && is_symbol(lines[i - 1][j - 1]))
        return 1;
    if (i > 0 && j < max_j && is_symbol(lines[i - 1][j + 1]))
        return 1;
    if (i < max_i && j > 0 && is_symbol(lines[i + 1][j - 1]))
        return 1;
    if (i < max_i && j < max_j && is_symbol(lines[i + 1][j + 1]))
        return 1;
    return 0;
}

Point_To_Star_Map *update_star_info(Point_To_Star_Map *point_to_star, Point_Set *star_neighbour_set, int num)
{
    for (int i = 0; i < hmlen(star_neighbour_set); i++)
    {
        Point starCoordinates = star_neighbour_set[i].key;
        Star starInfo = hmget(point_to_star, starCoordinates);
        starInfo.neighbourProduct *= num;
        starInfo.neighbourCount += 1;
        hmput(point_to_star, starCoordinates, starInfo);
    }
    return point_to_star;
}

Point_Set *update_star_neighbour_set(Point_To_Star_Map *point_to_star, Point_Set *star_neighbour_set, Point position)
{
    int r = position.x;
    int c = position.y;
    Point neighbours[] = {
        {r - 1, c}, {r + 1, c}, {r, c - 1}, {r, c + 1}, {r - 1, c - 1}, {r - 1, c + 1}, {r + 1, c - 1}, {r + 1, c + 1}};

    for (int i = 0; i < 8; i++)
    {
        if (hmgeti(point_to_star, neighbours[i]) >= 0)
        {
            hmput(star_neighbour_set, neighbours[i], 1);
        }
    }
    return star_neighbour_set;
}

long long int calculate_gear_ratio_from_star_info(Point_To_Star_Map *point_to_star)
{
    long long int total_gear_ratio = 0;
    for (int i = 0; i < hmlen(point_to_star); i++)
    {
        Star star = point_to_star[i].value;
        if (star.neighbourCount != 2)
            continue;
        total_gear_ratio += star.neighbourProduct;
    }
    return total_gear_ratio;
}

int part1(char **grid, int ROWS, int COLS)
{
    if (ROWS != COLS)
    {
        printf("ERROR: ROWS != COLS, ROWS: %i, COLS: %i\n", ROWS, COLS);
        return 1;
    }

    int part_number_sum = 0;
    int cur_num = 0;
    int is_cur_num_valid = 0;
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (isdigit(grid[r][c]))
            {
                cur_num = cur_num * 10 + (grid[r][c] - '0');
                if (at_least_one_neighbour_is_symbol(grid, r, c, ROWS - 1, COLS - 1))
                {
                    is_cur_num_valid = 1;
                }
            }
            else
            {
                if (is_cur_num_valid)
                    part_number_sum += cur_num;
                cur_num = 0;
                is_cur_num_valid = 0;
            }
        }
        if (is_cur_num_valid)
            part_number_sum += cur_num;
        cur_num = 0;
        is_cur_num_valid = 0;
    }
    return part_number_sum;
}

long long int part2(char **grid, int ROWS, int COLS)
{
    if (ROWS != COLS)
    {
        printf("ERROR: ROWS != COLS, ROWS: %i, COLS: %i\n", ROWS, COLS);
        return 1;
    }

    Point_To_Star_Map *point_to_star = NULL; // (star_x, star_y): {neighbourProduct, neighbourCount}
    // find all stars
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (grid[r][c] == '*')
            {
                Point star_coordinates = {r, c};
                Star new_star = {1, 0};
                hmput(point_to_star, star_coordinates, new_star);
            }
        }
    }

    int cur_num = 0;

    Point_Set *cur_star_neighbours_set = NULL; // Set {(x,y), (x,y), (x,y), (x,y)}
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (isdigit(grid[r][c]))
            {
                cur_num = cur_num * 10 + (grid[r][c] - '0');
                Point position = {r, c};
                cur_star_neighbours_set = update_star_neighbour_set(point_to_star, cur_star_neighbours_set, position);
            }
            else
            {
                point_to_star = update_star_info(point_to_star, cur_star_neighbours_set, cur_num);
                hmfree(cur_star_neighbours_set);
                cur_num = 0;
            }
        }
        point_to_star = update_star_info(point_to_star, cur_star_neighbours_set, cur_num);
        hmfree(cur_star_neighbours_set);
        cur_num = 0;
    }

    long long int total_gear_ratio = calculate_gear_ratio_from_star_info(point_to_star);

    hmfree(point_to_star);
    return total_gear_ratio;
}

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

    printf("Part 1: %i\n", part1(lines, linecount - 1, strlen(lines[0])));
    printf("Part 2: %lli\n", part2(lines, linecount - 1, strlen(lines[0])));
    return 0;
}
