#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day05"
run_test "part1" "./test_input.txt" "../main.c" "Part1 result: 35"
run_test "part2" "./test_input.txt" "../main2.c" "Part 2 sol: 46"