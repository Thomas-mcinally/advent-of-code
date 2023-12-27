#include <stdio.h>

// A bit hacky, use size_t to be able to deal with large Part2 values
// More robust to use the mpz_t type from the GNU MP library
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
    const size_t N = 4;
    const size_t times[] = {59, 79, 65, 75};
    const size_t distances[] = {597, 1234, 1032, 1328};
    size_t total_error_margin = 1;
    for (size_t i = 0; i < N; i++)
    {
        size_t number_of_ways = number_of_ways_to_win(times[i], distances[i]);
        total_error_margin *= number_of_ways;
    }

    printf("Part1 sol: %zu\n", total_error_margin);

    size_t corrected_time = 59796575;
    size_t corrected_distance = 597123410321328;
    printf("Part2 sol: %zu\n", number_of_ways_to_win(corrected_time, corrected_distance));

    return 0;
}
