#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day04"
run_test "part1" "./test_input.txt" "../main.c" "Part1: 13"
run_test "part2" "./test_input.txt" "../main.c" "Part2: 30"