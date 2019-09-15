import sys


def shift_text(plain_text, key):
    cipher_text = ""
    plain_text_ord = [ord(x) for x in plain_text]
    key_list = [ord(x) - 65 if ord(x) < 97 else ord(x) - 97 for x in key]
    j = 0

    for i, val in enumerate(plain_text_ord):
        if not chr(val).isalpha():
            cipher_text += chr(val)
        else:
            char = chr(val + key_list[j % len(key_list)])
            if (plain_text[i].islower() and ord(char) > ord('z')) or (plain_text[i].isupper() and ord(char) > ord('Z')):
                char = chr(ord(char) - 26)
            cipher_text += char
            j += 1

    return cipher_text


if len(sys.argv) > 2 or not sys.argv[1].isalpha():
    print('Usage: python vigenere.py k')
    sys.exit()
else:
    shift_word = sys.argv[1]

    while True:
        plain_text = input("plaintext: ")
        if not len(plain_text) == 0:
            break

    print("ciphertext: " + shift_text(plain_text, shift_word))