#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day13"
run_test "part1" "./test_input.txt" "../main.c" "Answer to part 1 = 405"
run_test "part2" "./test_input.txt" "../main.c" "Answer to part 2 = 400"