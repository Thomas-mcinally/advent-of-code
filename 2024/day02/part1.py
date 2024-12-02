
with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

safe_reports = 0
for report in lines:
    is_safe = True
    levels = [int(item) for item in report.split(" ")]
    is_increasing = levels[0] < levels[1]
    for i in range(1,len(levels)):
        if is_increasing==True and levels[i] > levels[i-1] and abs(levels[i]-levels[i-1]) <= 3:
            continue
        if is_increasing==False and levels[i] < levels[i-1] and abs(levels[i]-levels[i-1]) <= 3:
            continue
        is_safe = False

    if is_safe:
        safe_reports += 1

print(safe_reports)
