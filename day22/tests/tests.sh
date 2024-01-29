#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day22"
if ! run_test "part1" "./test_input.txt" "../main.c" "Part1 sol: 5"; then
    exit 1
fi
if ! run_test "part2" "./test_input.txt" "../main.c" "Part2 sol: 7"; then
    exit 1
fi

