#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc_lib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

char order_of_chars[] = "AKQJT98765432";

int custom_compare(const void *a, const void *b)
{
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;

    for (size_t i = 0; i < strlen(str_a); i++)
    {
        int index_a = strchr(order_of_chars, str_a[i]) - order_of_chars;
        int index_b = strchr(order_of_chars, str_b[i]) - order_of_chars;

        if (index_a != index_b)
        {
            return index_a - index_b;
        }
    }
    // this line should never be reached
    return 1;
}

void sort_hands_into_buckets(char **hands, size_t num_hands, char **buckets[]) {
    char possible_chars[] = "AKQJT98765432";
    for (int i=0; i<num_hands; i++) {
        int counts[13] = {0};
        int three_of_a_kind = 0;
        int two_of_a_kind = 0;
        int four_of_a_kind = 0;
        int five_of_a_kind = 0;
        for (int j=0; j<5; j++) {
            int index = strchr(possible_chars, hands[i][j]) - possible_chars;
            counts[index]++;
            if (counts[index] == 2) two_of_a_kind++;
            else if (counts[index] == 3) {
                three_of_a_kind++;
                two_of_a_kind--;
            }
            else if (counts[index] == 4) four_of_a_kind++;
            else if (counts[index] == 5) five_of_a_kind++;
        }
        if (five_of_a_kind) arrput(buckets[0], hands[i]);
        else if (four_of_a_kind) arrput(buckets[1], hands[i]);
        else if (three_of_a_kind && two_of_a_kind) arrput(buckets[2], hands[i]);
        else if (three_of_a_kind) arrput(buckets[3], hands[i]);
        else if (two_of_a_kind == 2) arrput(buckets[4], hands[i]);
        else if (two_of_a_kind) arrput(buckets[5], hands[i]);
        else arrput(buckets[6], hands[i]);
    }
}

void sort_hands_into_buckets_part2(char **hands, size_t num_hands, char **buckets[]){
    char possible_chars[] = "JAKQT98765432";
    for (int i = 0; i < num_hands; i++)
    {
        int counts[13] = {0};
        int three_of_a_kind = 0;
        int two_of_a_kind = 0;
        int four_of_a_kind = 0;
        int five_of_a_kind = 0;
        for (int j = 0; j < 5; j++)
        {
            int index = strchr(possible_chars, hands[i][j]) - possible_chars;
            counts[index]++;
            if (index ==0) continue;
            else if (counts[index] == 2)
                two_of_a_kind++;
            else if (counts[index] == 3)
            {
                three_of_a_kind++;
                two_of_a_kind--;
            }
            else if (counts[index] == 4)
                four_of_a_kind++;
            else if (counts[index] == 5)
                five_of_a_kind++;
        }
        while (counts[0] > 0)
        {
            if (four_of_a_kind) {four_of_a_kind--;five_of_a_kind++;counts[0]--;continue;}
            if (three_of_a_kind) {three_of_a_kind--;four_of_a_kind++;counts[0]--;continue;}
            if (two_of_a_kind) {two_of_a_kind--;three_of_a_kind++;counts[0]--;continue;}
            two_of_a_kind++;counts[0]--;
        }
        if (five_of_a_kind) arrput(buckets[0], hands[i]);
        else if (four_of_a_kind) arrput(buckets[1], hands[i]);
        else if (three_of_a_kind && two_of_a_kind) arrput(buckets[2], hands[i]);
        else if (three_of_a_kind) arrput(buckets[3], hands[i]);
        else if (two_of_a_kind == 2) arrput(buckets[4], hands[i]);
        else if (two_of_a_kind) arrput(buckets[5], hands[i]);
        else arrput(buckets[6], hands[i]);
    }
}

size_t calculate_score_from_buckets(char **buckets[], int item_count) {
    size_t total = 0;
    int rank = item_count;
    for (int i=0; i<7; i++) {
        if (*buckets[i] == NULL) continue;
        qsort(buckets[i], arrlen(buckets[i]), sizeof(buckets[i][0]), custom_compare);
        
        for (int j=0; j<arrlen(buckets[i]); j++) {
            int bid = extract_number_from_string(buckets[i][j]+6);
            total += bid * rank;
            rank--;
        }
    }
    return total;
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

    char **buckets[7] = {NULL};
    sort_hands_into_buckets(lines, linecount, buckets);
    size_t part1_total = calculate_score_from_buckets(buckets, linecount);
    for (int i=0; i<7; i++) arrfree(buckets[i]);
    
    strcpy(order_of_chars, "AKQT98765432J");
    sort_hands_into_buckets_part2(lines, linecount, buckets);
    size_t part2_total = calculate_score_from_buckets(buckets, linecount);
    for (int i=0; i<7; i++) arrfree(buckets[i]);
    for (int i=0; i<linecount; i++) free(lines[i]);
    free(lines);


    printf("part1: %zu\n", part1_total);
    printf("part2: %zu\n", part2_total);

    return 0;
}


// O(N) time complexity
// 7 buckets, one for each hand type. Bucket 1 is for high card, bucket 7 is for 5-of-a-kind
// iterate through hands and place them in buckets

// O(N^2) with qsort
// Sort each bucket by card value. (Value order A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2)
// Maybe there is a smart way to do this?

// O(N) time complexity
// Iterate through each hand and add up total.
