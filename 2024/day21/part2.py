from functools import cache

INPUT = {
    # simplified problem by manually doing first translation
    # the strings are possible optimal ways to indirectly type input on numeric keypad, using a directional keypad
    # Multiple possible optimal ways per input. 
        # e.g. Not sure if can deterministically say ^^AvA<^^Avvv>A worse/better than ^^AvA^^<Avvv>A
    671: ["^^A^<<AvvA>>vA", "^^A<<^AvvA>>vA"],
    83: ["<A^^^A>vvAvA", "<A^^^Avv>AvA"],
    582: ["<^^A^AvvAv>A", "^^<A^AvvAv>A", "<^^A^AvvA>vA", "^^<A^AvvA>vA"],
    638: ["^^AvA<^^Avvv>A", "^^AvA^^<Avvv>A", "^^AvA<^^A>vvvA", "^^AvA^^<A>vvvA"],
    341: ["^A^<<AvA>>vA", "^A<<^AvA>>vA"]
}

@cache 
def type_using_directional(prev_char, char, repetitions) -> int:
    """how to type char into directional keypad, using another directional keypad"""

    PATH_TO_MIN_INSTRUCTIONS = { 
        #(start, end): instructions
        ("^", "A"): ">A",
        ("^", "<"): "v<A",
        ("^", "v"): "vA",
        ("^", ">"): "v>A",

        ("A", "^"): "<A",
        ("A", "<"): "v<<A",
        ("A", "v"): "<vA",
        ("A", ">"): "vA",

        ("<", "^"): ">^A",
        ("<", "A"): ">>^A",
        ("<", "v"): ">A",
        ("<", ">"): ">>A",

        ("v", "^"): "^A",
        ("v", "A"): "^>A",
        ("v", "<"): "<A",
        ("v", ">"): ">A",

        (">", "^"): "<^A",
        (">", "A"): "^A",
        (">", "<"): "<<A",
        (">", "v"): "<A",
    }
    direct = PATH_TO_MIN_INSTRUCTIONS[(prev_char, char)] if prev_char != char else "A"
    if repetitions == 0:
        return len(direct)
    
    output = 0
    prev = "A"
    for c in direct:
        output += type_using_directional(prev, c, repetitions-1)
        prev=c
    return output




total_complexity = 0
for numeric, options in INPUT.items():
    best_option = float("inf")
    for base in options:
        result = 0
        prev = "A"
        for c in base:
            result += type_using_directional(prev, c, 24)
            prev = c
        
        best_option = min(best_option, result)
    total_complexity += best_option * numeric
print(total_complexity)

