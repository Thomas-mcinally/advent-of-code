#!/bin/bash
set -e
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day15"
run_test "part1" "./test_input.txt" "../main.c" "Part1 sol: 1320"
run_test "part2" "./test_input.txt" "../main.c" "Part2 sol: 145"

