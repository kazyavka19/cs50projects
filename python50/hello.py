from cs50 import get_int, get_string
from sys import argv


def main(argv):
   if len(argv) == 2:
       print(f"Hello, {argv[1]}!")
   else:
       print("Hello, world!")

def hello():
    print("hello, world")

def number_example():
    x = get_int("Number: ")
    print(x)

def name_example():
    answer = get_string("What is your name? ")
    print(f"hello, {answer}")

def math_example():
    x = get_int("x: ")
    y = get_int("y: ")
    print(x + y)

def agreement_example():
    s = input("Do you agree? ").lower()

    if s in ["y", "yes"]:
        print("Agreed.")
    elif s in ["n", "no"]:
        print("Not agreed.")
    else:
        print("Invalid input.")

def uppercase_example():
    before = input("Before: ")
    print(f"After: {before.upper()}")

def meow(n):
    for _ in range(n):
        print("meow")

def is_int():
    n = input("Integer: ")
    if n.isnumeric():
        print("Integer.")
    else:        
        print("Not an integer.")


def try_example():
    try:
        x = int(input("Integer: "))
    except ValueError:
        print("Not an integer.")
    else:
        print(f"x is {x}")


def mario1():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0:
                break
        except ValueError:
            continue

    #for row in range(n):
    #    for space in range(n - row - 1):
    #        print(" ", end="")      
    #    for hashtag in range(row + 1):
    #        print("#", end="")
    #    print()

    for row in range(n):
        print(" " * (n - row - 1), end="")
        print("#" * (row + 1), end="")
        print()

         
def mario2():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0:
                break
        except ValueError:
            print("Not an integer.")
            continue
       
    for row in range(n):
        print("#" * (row + 1), end="")
        print(" " * (n - row - 1), end="")
        print()

def scores(n):
    scores = []

    for i in range(n):
        score = get_int("Score: ")
        scores.append(score)

    avg = sum(scores) / len(scores)
    print(f"Average: {avg}")

def phonebook():
    niggas = [
        {"name": "tyron", "number": "123-456-7890"},
        {"name": "jamal", "number": "098-765-4321"},
        {"name": "ALBLAK 52", "number": "+7(952)812"}
    ]

    name = input("Name: ")
    for nigga in niggas:
        if nigga["name"] == name:
            number = nigga["number"]
            print(f"Number: {number}")
            break
    else:
            print("Name not found.")



if __name__ == "__main__":
    main(argv)
