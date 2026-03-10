def main():
    mario1()

def mario1():
    while True:
        try:
            x = int(input("Height: "))
            if x > 0:
                break
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    
    for row in range(x):
        print(" " * (x - row - 1), end="")
        print("#" * (row + 1), end="")
        print()



def mario2():
    while True:
        try:
            x = int(input("Height: "))
            if x > 0:
                break
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    
    for row in range(x):
        print("#" * (row + 1), end="")
        print(" " * (x - row - 1), end="")
        print()


main()