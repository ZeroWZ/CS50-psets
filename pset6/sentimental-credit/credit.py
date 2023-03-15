# TODO
from cs50 import get_string


def main():
    number = get_string("Number: ")

    l = len(number)
    vld = validation_character(number, l)
    
    if vld == 0:
        type(number, l)
    else:
        print("INVALID")
        
# Checking if the number is a valid card number


def validation_character(number, l):
    j = 0
    # Calculate checksum
    while l > 1:
        i = int(number[l - 2]) * 2
        if i < 10:
            j = j + i
        else:
            s = str(i)
            i = int(s[0]) + int(s[1])
            j = j + i
        l -= 2

    l = len(number)
    while l > 0:
        n = int(number[l - 1])
        j = j + n
        l -= 2

    j = j % 10

    if j == 0:
        return 0
    else:
        return 1
        
# AMEX or MASTERCARD or VISA


def type(number, l):
    n = int(number[0]) * 10 + int(number[1])
    m = int(number[0])
    
    if l == 15 and (n == 34 or n == 37):
        print("AMEX")
    elif l == 16 and (n == 51 or n == 52 or n == 53 or n == 54 or n == 55):
        print("MASTERCARD")
    elif (l == 13 or l == 16) and m == 4:
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()