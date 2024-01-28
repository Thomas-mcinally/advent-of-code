#!/bin/bash

gcc main2.c ../libs/aoc_lib.c -I ../libs

output=$(./a.out input.txt)
expected_output="Part2 sol: 54518"

if [ "$output" = "$expected_output" ]; then
    echo "Test passed"
else
    echo "Test failed: expected '$expected_output', got '$output'"
fi