#!/bin/bash

gcc main.c ../libs/aoc_lib.c -I ../libs

output=$(./a.out input.txt)
expected_output="Part1 sol: 54331"

if [ "$output" = "$expected_output" ]; then
    echo "Test passed"
else
    echo "Test failed: expected '$expected_output', got '$output'"
fi