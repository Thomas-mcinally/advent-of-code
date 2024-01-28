#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day03"
run_test "part1" "./test_input.txt" "../main.c" "Part 1: 4361"
run_test "part1" "./test_input.txt" "../main.c" "Part 2: 467835"