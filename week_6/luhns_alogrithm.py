while True:
    cc = input('Number: ')
    if not (13 <= len(cc) <= 16) and not cc.isdigit():
        print('Please enter a valid 16 digit value.')
        continue
    else:
        break


def cardtype(cc):
    AMEX = ['34', '37']
    MASTERCARD = ['51', '52', '53', '54', '55']
    VISA = '4'

    if ''.join(cc[0:2]) in AMEX:
        return 'AMEX\n'
    elif ''.join(cc[0:2]) in MASTERCARD:
        return 'MASTERCARD\n'
    elif cc[0] == VISA:
        return 'VISA\n'
    else:
        return 'INVALID\n'


def is_valid(cc):
    first_pass = ''.join([str(int(x) * 2) for ind, x in enumerate(cc[::-1]) if ind % 2 != 0])

    temp = 0
    for x in first_pass:
        temp += int(x)

    if len(cc) % 2 != 0:
        second_pass = sum(map(int, cc[0::2]))
    else:
        second_pass = sum(map(int, cc[1::2]))

    return (temp + second_pass) % 10 == 0


if is_valid(cc):
    print(cardtype(cc))
else:
    print('INVALID\n')