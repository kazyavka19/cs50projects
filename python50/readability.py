def main():
    readability()

def readability():
    text = input("Text: ")
    words = text.split()
    sentences = text.count(".") + text.count("!") + text.count("?")
    letters = sum(c.isalpha() for c in text)

    L = letters / len(words) * 100
    S = sentences / len(words) * 100

    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()