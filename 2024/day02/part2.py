
with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

def nums_is_increasing_starting_from(arr: list[int], cache: dict, i: int, prev_i: int, skip_used: bool) -> bool:
    if (i, prev_i, skip_used) in cache:
        return cache[(i, prev_i, skip_used)]
    if i == len(arr):
        return True

    result = False
    if prev_i==-1 or (arr[i] > arr[prev_i] and abs(arr[i] - arr[prev_i]) <= 3):
        result = result or nums_is_increasing_starting_from(arr, cache, i+1, i, skip_used) #take
    if skip_used == False:
        result = result or nums_is_increasing_starting_from(arr, cache, i+1, prev_i, True) #skip
    cache[(i, prev_i, skip_used)] = result
    return result



safe_reports = 0
for report in lines:
    levels = [int(item) for item in report.split(" ")]
    if nums_is_increasing_starting_from(levels[::-1], {}, 0, -1, False) or nums_is_increasing_starting_from(levels, {}, 0, -1, False):
        safe_reports += 1 

print(safe_reports)
