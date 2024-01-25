#include <stdio.h>

size_t number_of_ways_to_win(size_t time_limit, size_t record_distance)
{
    size_t l = 0;
    size_t r = time_limit;
    while (l <= r)
    {
        size_t mid = l + (r - l) / 2;
        size_t distance_traveled = (time_limit - mid) * mid;
        if (distance_traveled > record_distance)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return time_limit - r * 2 - 1;
}

int main()
{
    int times[] = {59, 79, 65, 75};
    int distances[] = {597, 1234, 1032, 1328};
    size_t part1_result = 1;
    for (int i = 0; i < 4; i++)
    {
        part1_result *= number_of_ways_to_win(times[i], distances[i]);
    }

    printf("Part1 sol: %zu\n", part1_result);

    size_t part_2_time = 59796575;
    size_t part_2_distance = 597123410321328;
    size_t part2_result = number_of_ways_to_win(part_2_time, part_2_distance);
    printf("Part2 sol: %zu\n", part2_result);

    return 0;
}
