#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day06"
run_test "part1" "./test_input.txt" "../main.c" "Part1 sol: 288"
run_test "part2" "./test_input2.txt" "../main2.c" "Part2 sol: 71503"