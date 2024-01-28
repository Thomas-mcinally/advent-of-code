#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day20"
if !run_test "part1" "./test_input.txt" "../main.c" "Part1 sol: 32000000"; then
    exit 1
fi