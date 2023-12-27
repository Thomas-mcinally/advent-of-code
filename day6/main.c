#include <stdio.h>

// assume inputs fit in 64-bit unsigned int

long long unsigned int number_of_ways_to_win(long long unsigned int time_limit, long long unsigned int record_distance)
{
    long long unsigned int l = 0;
    long long unsigned int r = time_limit;
    while (l <= r)
    {
        long long unsigned int mid = l + (r - l) / 2;
        long long unsigned int distance_traveled = (time_limit - mid) * mid;
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
    int part1_result = 1;
    for (int i = 0; i < 4; i++)
    {
        int number_of_ways = number_of_ways_to_win(times[i], distances[i]);
        part1_result *= number_of_ways;
    }

    printf("Part1 sol: %i\n", part1_result);

    long long unsigned int corrected_time = 59796575;
    long long unsigned int corrected_distance = 597123410321328;
    long long unsigned int part2_result = number_of_ways_to_win(corrected_time, corrected_distance);
    printf("Part2 sol: %llu\n", part2_result);

    return 0;
}
