def smudges_required_for_valid_palindrome_centered_at(s, l,r):
    smudges = 0
    while l >= 0 and r < len(s):
        if s[l] != s[r]:
            smudges += 1
        l-=1
        r+=1
    return smudges

def vertical_mirror_score(chunk, score_multiplier, target_smudge_count):
    ROWS = len(chunk)
    COLS = len(chunk[0])

    for c in range(COLS-1):
        smudges_required_for_vertical_mirror = 0
        for r in range(ROWS):
            smudges_required_for_vertical_mirror += smudges_required_for_valid_palindrome_centered_at(chunk[r], c, c+1)

        if smudges_required_for_vertical_mirror == target_smudge_count:
            return (c+1) * score_multiplier
    return 0


with open("input.txt", "r") as file:
    input = file.read()
    chunks = input.split("\n\n")
    chunks = [chunk.split("\n") for chunk in chunks]

part1_total = 0
part2_total = 0
for chunk in chunks:
    part1_total += vertical_mirror_score(chunk, 1, 0)
    part2_total += vertical_mirror_score(chunk, 1, 1)
    
rotated_chunks = [list(zip(*chunk)) for chunk in chunks]
for chunk in rotated_chunks:
    part1_total += vertical_mirror_score(chunk, 100, 0)
    part2_total += vertical_mirror_score(chunk, 100, 1)

print(f"part1 result: {part1_total}")
print(f"part2 result: {part2_total}")