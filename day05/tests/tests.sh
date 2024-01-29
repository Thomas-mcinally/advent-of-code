#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day05"
if ! run_test "part1" "./test_input.txt" "../main.c" "Part1 sol: 35"; then
    exit 1
fi
if ! run_test "part2" "./test_input.txt" "../main2.c" "Part2 sol: 46"; then
    exit 1
fi

