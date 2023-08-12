from cs50 import get_string


def count_letters(string):
    # Count the number of letters
    count = 0
    string = string.lower()

    for i in range(len(string)):
        if string[i].isalpha():
            count += 1

    return count


def count_words(string):
    # Count the number of words
    count = 1
    string = string.lower()

    for i in range(len(string)):
        if string[i].isspace():
            count += 1

    return count


def count_sentences(string):
    # Count the number of sentences
    count = 0
    string = string.lower()

    for i in range(len(string)):
        if (string[i] == '.' or string[i] == '?' or string[i] == '!'):
            count += 1

    return count


def main():
    string = get_string("Introduce the text: ")         # Prompt the user for the text

    L = (count_letters(string) / count_words(string)) * 100     # Avg number of letters per 100 words in the text
    S = (count_sentences(string) / count_words(string)) * 100   # Avg number of sentences per 100 words in the text

    index = (0.0588 * L) - (0.296 * S) - 15.8          # Coleman-Liau Index

    if index < 1:                                            # Printing the Grade
        print("Before Grade 1")
    elif (index >= 16):
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


if __name__ == '__main__':
    main()