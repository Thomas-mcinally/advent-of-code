#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day07"
if ! run_test "part1" "./test_input.txt" "../main.c" "Part1 sol: 6440"; then
    exit 1
fi
if ! run_test "part2" "./test_input.txt" "../main.c" "Part2 sol: 5905"; then
    exit 1
fi