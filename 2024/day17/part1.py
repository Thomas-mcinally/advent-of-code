import re


def run_program(program: list[int], reg_a_init: int, reg_b_init: int, reg_c_init: int) -> list[str]:
    reg_a = reg_a_init
    reg_b = reg_b_init
    reg_c = reg_c_init
    output = []
    def get_combo_operand(operand):
        if operand == 7:
            raise
        if operand <= 3:
            return operand
        if operand == 4:
            return reg_a
        if operand == 5:
            return reg_b
        if operand == 6:
            return reg_c
    
    i = 0
    while i < len(program)-1:
        instruction, operand = program[i], program[i+1]

        if instruction == 0:
            combo_operand = get_combo_operand(operand)
            numerator = reg_a
            denominator = 2**combo_operand
            reg_a = numerator // denominator

        elif instruction == 6:
            combo_operand = get_combo_operand(operand)
            numerator = reg_a
            denominator = 2**combo_operand
            reg_b = numerator // denominator

        elif instruction == 7:
            combo_operand = get_combo_operand(operand)
            numerator = reg_a
            denominator = 2**combo_operand
            reg_c = numerator // denominator

        elif instruction == 1:
            reg_b ^= operand
        
        elif instruction == 2:
            combo_operand = get_combo_operand(operand)
            reg_b = combo_operand%8
        
        elif instruction == 3:
            if reg_a:
                i = operand
                continue
        
        elif instruction == 4:
            reg_b ^= reg_c
        
        elif instruction == 5:
            combo_operand = get_combo_operand(operand)
            output.append(str(combo_operand%8))
        print(reg_a)
        i += 2
    return output

with open("input.txt") as f:
    s = f.read().strip()

all_nums = [int(num) for num in re.findall(r'(-?\d+)', s)]

result = run_program(all_nums[3:], all_nums[0], all_nums[1], all_nums[2])
print("output:")
print(",".join(result))