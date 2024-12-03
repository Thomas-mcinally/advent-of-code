with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()


result = 0
for line in lines:
    for i, char in enumerate(line):
        if line[i:i+4] != "mul(":
            continue
        try:
            comma_idx = line.find(",", i+4)
            end_parenthesis_idx = line.find(")", i+4)
            num1 = int(line[i+4:comma_idx])
            num2 = int(line[comma_idx+1: end_parenthesis_idx])
            result += num1*num2
        except Exception:
            continue
        

print(result)


