def main():
    cash()

def cash():
    while True:
        try:
            x = float(input("Channge owed: "))
            if x > 0:
                break
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    
    x = round(x * 100)
    coins = 0

    if x >= 25:
        x -= 25
        coins += 1

    if x >= 10:
        x -= 10
        coins += 1

    if x >= 5:
        x -= 5
        coins += 1
       
    if x >= 1:
        x -= 1
        coins += 1

    print(coins)

if __name__ == "__main__":
    main()