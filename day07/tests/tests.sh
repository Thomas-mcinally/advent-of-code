#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day07"
run_test "part1" "./test_input.txt" "../main.c" "part1: 6440"
run_test "part2" "./test_input.txt" "../main.c" "part2: 5905"