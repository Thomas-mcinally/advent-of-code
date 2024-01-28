#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day12"
run_test "part1" "./test_input.txt" "../main.c" "Total combos: 21"
run_test "part2" "./test_input.txt" "../main.c" "Total combos part 2: 525152"