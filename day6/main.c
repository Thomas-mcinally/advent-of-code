#include <stdio.h>
#include <gmp.h>

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

void number_of_ways_to_win_large(char *time_limit, char *record_distance)
{
    mpz_t l, r, mid, distance_traveled, result, record_distance_bigint, time_limit_bigint, one, two;
    mpz_init(l);
    mpz_init(r);
    mpz_init(mid);
    mpz_init(distance_traveled);
    mpz_init(result);
    mpz_init_set_str(time_limit_bigint, time_limit, 10);
    mpz_init_set_str(record_distance_bigint, record_distance, 10);
    mpz_init_set_str(one, "1", 10);
    mpz_init_set_str(two, "2", 10);

    mpz_set_str(l, "0", 10);
    mpz_set_str(r, time_limit, 10);

    while (mpz_cmp(l, r) <= 0)
    {
        mpz_add(mid, l, r);
        mpz_tdiv_q(mid, mid, two);
        mpz_sub(distance_traveled, time_limit_bigint, mid);
        mpz_mul(distance_traveled, distance_traveled, mid);
        if (mpz_cmp(distance_traveled, record_distance_bigint) > 0) mpz_sub(r, mid, one);
        else mpz_add(l, mid, one);
    }

    mpz_sub(result, time_limit_bigint, r);
    mpz_sub(result, result, r);
    mpz_sub(result, result, one);
    gmp_printf("Part2 sol: %Zd\n", result);
    mpz_clear(l);
    mpz_clear(r);
    mpz_clear(mid);
    mpz_clear(distance_traveled);
    mpz_clear(result);
    mpz_clear(record_distance_bigint);
    mpz_clear(time_limit_bigint);
    mpz_clear(one);
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
    number_of_ways_to_win_large("59796575", "597123410321328");

    return 0;
}
