#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day21"
run_test "part1" "./test_input.txt" "../main.c" "part1 result: 43"
run_test "part2" "./test_input.txt" "../main.c" "part2 result: 3314963864838"