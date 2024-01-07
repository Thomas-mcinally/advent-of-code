def is_valid_palindrome_centered_at(s, l,r):
    while l >= 0 and r < len(s) and s[l] == s[r]:
        l-=1
        r+=1
    if l == -1 or r == len(s): return True
    return False

def score_from_chunk(chunk, score_multiplier):
    ROWS = len(chunk)
    COLS = len(chunk[0])
    possible_vertical_mirror = [True] * (COLS-1)
    for r in range(ROWS):
          for c in range(COLS-1):
            if not possible_vertical_mirror[c]: continue
            possible_vertical_mirror[c] = is_valid_palindrome_centered_at(chunk[r], c, c+1)

    score = 0
    for i in range(len(possible_vertical_mirror)):
        if possible_vertical_mirror[i]:
            score += (i+1) * score_multiplier
    return score


with open("input.txt", "r") as file:
    input = file.read()
    chunks = input.split("\n\n")
    chunks = [chunk.split("\n") for chunk in chunks]

total = 0
for chunk in chunks:
    total += score_from_chunk(chunk, 1)
    
rotated_chunks = [list(zip(*chunk)) for chunk in chunks]
for chunk in rotated_chunks:
    total += score_from_chunk(chunk, 100)

print(f"part1 result: {total}")