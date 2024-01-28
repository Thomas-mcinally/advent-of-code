#!/bin/bash

gcc ../main.c ../../libs/aoc_lib.c -I ../../libs

output=$(./a.out input1.txt)
expected_output="Part1 sol: 142"

if [ "$output" = "$expected_output" ]; then
    echo "Test passed"
else
    echo "Test failed: expected '$expected_output', got '$output'"
fi