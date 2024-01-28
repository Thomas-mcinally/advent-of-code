#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day19"
run_test "part1" "./test_input.txt" "../main.c" "Part1 sol: 19114"
run_test "part2" "./test_input.txt" "../main.c" "Part2 sol: 167409079868000"