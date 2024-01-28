#!/bin/bash

test_name="part2"
input_file_path="./input2.txt"
build_command="gcc ../main2.c ../../libs/aoc_lib.c -I ../../libs"
expected_output="Part2 sol: 281"

cd "$(dirname "$0")"
eval $build_command
output=$(./a.out $input_file_path)

if [ "$output" = "$expected_output" ]; then
    echo "Test $test_name passed"
else
    echo "Test $test_name failed: expected '$expected_output', got '$output'"
fi

rm a.out