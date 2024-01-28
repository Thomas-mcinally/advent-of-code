#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day01"
if ! run_test "part1" "./input1.txt" "../main.c" "Part1 sol: 145"; then
    exit 1
fi

if ! run_test "part2" "./input2.txt" "../main2.c" "Part2 sol: 281"; then
    exit 1
fi