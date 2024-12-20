
def can_form_starting_from(pattern, words, i, cache):
    if i in cache:
        return cache[i]
    if i == len(pattern):
        return True

    result = False
    for word in words:
        if pattern[i:i+len(word)] == word:
            result = result or can_form_starting_from(pattern, words, i+len(word), cache)
    
    cache[i] = result
    return result



with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

words = set([word.strip() for word in lines[0].split(",")])
patterns = lines[2:]
valid_patterns = 0
for pattern in patterns:
    valid_patterns += 1 if can_form_starting_from(pattern, words, 0, {}) else 0

print(valid_patterns)

# Time O(P * N*W*L)
    # For each pattern 
    # N unique inputs to func (i), each of these func calls iterate over W words, each of these words slices a string of lenght L

# Space O(N) - Recursion call stack and size of cache. Cache reset for each pattern


# More optimal solution using Trie possible -> Time O(P * N^2)