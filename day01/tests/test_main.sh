#!/bin/bash

test_name="part1"
input_file_path="./input1.txt"
build_command="gcc ../main.c ../../libs/aoc_lib.c -I ../../libs"
expected_output="Part1 sol: 142"

cd "$(dirname "$0")"
eval $build_command
output=$(./a.out $input_file_path)
rm a.out

if [ "$output" = "$expected_output" ]; then
    echo "Test $test_name passed"
else
    echo "Test $test_name failed: expected '$expected_output', got '$output'"
    exit 1
fi