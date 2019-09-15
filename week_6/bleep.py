from cs50 import get_string
from sys import argv


def get_arg():
    if len(argv) > 2:
        print('Usage: python bleep.py dictionary')
        exit(1)
        return False
    else:
        return argv[1]


def tokenize_words(file):
    with open(file, 'r') as f:
        banned_words = f.readlines()
    return set(map(str.strip, banned_words))


def parse_input(banned_words, user_input):
    bleeped = []
    for word in user_input:
        if word.lower() in banned_words:
            bleeped.append('*' * len(word))
        else:
            bleeped.append(word)
    return bleeped


def main():
    file = get_arg()

    banned_words = tokenize_words(file)
    user_input = input('Please enter your words: ').split(' ')
    parsed_input = parse_input(banned_words, user_input)

    print(' '.join(parsed_input))


if __name__ == "__main__":
    main()
