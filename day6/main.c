#include <stdio.h>

int number_of_ways_to_win(int time_limit, int record_distance)
{
    int l = 0;
    int r = time_limit;
    while (l <= r)
    {
        int mid = l + (r-l)/2;
        int distance_traveled = (time_limit-mid) * mid;
        if (distance_traveled > record_distance) r = mid-1;
        else l = mid+1;
    }
    return time_limit - r*2 - 1;
}

int main()
{
    const int N = 4;
    const int times[] = {59,79,65,75};
    const int distances[] = {597,1234,1032,1328};

    int total_error_margin = 1;

    for (int i = 0; i < N; i++)
    {
        int number_of_ways = number_of_ways_to_win(times[i], distances[i]);
        total_error_margin *= number_of_ways;
    }

    printf("Part1 sol: %d\n", total_error_margin);
    return 0;
}
