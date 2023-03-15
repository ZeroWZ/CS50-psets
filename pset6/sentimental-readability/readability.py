# TODO
from cs50 import get_string


def main():
    text = get_string("Text: ")

    l_c = letters_counter(text)
    w_c = words_counter(text)
    s_c = sentences_counter(text)

    # Calculation of the Coleman-Liau Index
    L = l_c * 100 / w_c
    S = s_c * 100 / w_c
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # print the results
    if index < 1:
        print("Before Grade 1")

    elif index > 12:
        print("Grade 16+")

    else:
        print(f"Grade {index}")


# count the number of letters


def letters_counter(text):
    l_c = 0
    for c in text:
        if c.lower() >= "a" and c.lower() <= "z":
            l_c += 1

    return l_c

# count the number of words


def words_counter(text):
    w_c = 0
    for c in text:
        if c == ' ':
            w_c += 1

    return w_c + 1

# count the number of sentences


def sentences_counter(text):
    s_c = 0
    for c in text:
        if c == '!' or c == '.' or c == '?':
            s_c += 1

    return s_c


if __name__ == "__main__":
    main()