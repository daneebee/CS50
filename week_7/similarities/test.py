def parse_substr(text, length):
    parsed_substr = []

    for i in range(len(text)):
        print(text[i:i+length].rstrip())
        parsed_substr.append(text[i:i+length].rstrip())

    print([word for word in parsed_substr if len(word) == length])

    return [word for word in parsed_substr if len(word) == length]

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    a_substrs = parse_substr(a, n)
    b_substrs = parse_substr(b, n)

    matched_substrs = []
    for sub in a_substrs:
        if sub in b_substrs:
            matched_substrs.append(sub)

    return set(matched_substrs)


substrings('foobar', 'bar', 3)