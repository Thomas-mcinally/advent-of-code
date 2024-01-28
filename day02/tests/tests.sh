#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day02"
run_test "part1" "./test_input.txt" "../main.c" "part1 solution: 8"
run_test "part2" "./test_input.txt" "../main.c" "part2 solution: 2286"