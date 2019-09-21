from nltk.tokenize import sent_tokenize


def parse_lines(data):
    parsed_data = data.split("\n")
    parsed_data = set([line.rstrip() for line in parsed_data])
    return parsed_data


def lines(a, b):
    """Return lines in both a and b"""
    a_parsed = parse_lines(a)
    b_parsed = parse_lines(b)

    matched_lines = []
    for line in a_parsed:
        if line in b_parsed:
            matched_lines.append(line)

    return matched_lines


def sentences(a, b):
    """Return sentences in both a and b"""
    a_tokenized = set(sent_tokenize(a))
    b_tokenized = set(sent_tokenize(b))

    matched_sentences = []
    for sent in a_tokenized:
        if sent in b_tokenized:
            matched_sentences.append(sent)

    return matched_sentences


def parse_substr(text, length):
    parsed_substr = []

    for i in range(len(text)):
        tmp = text[i:i+length].rstrip()
        if len(tmp) == length:
            parsed_substr.append(tmp)

    return set(parsed_substr)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    a_substrs = parse_substr(a, n)
    b_substrs = parse_substr(b, n)

    matched_substrs = []
    for sub in a_substrs:
        if sub in b_substrs:
            matched_substrs.append(sub)

    return set(matched_substrs)
