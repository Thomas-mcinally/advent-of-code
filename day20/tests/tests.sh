#!/bin/bash
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day20"
run_test "part1" "./test_input.txt" "../main.c" "part1 result: 32000000"