def main():
    credit()

def is_valid_luhn(n):
    sum = 0
    alt = False

    while n > 0:
        digit = n % 10
        n //= 10

        if alt:
            digit *= 2
            if digit > 9:
                digit -= 9

        sum += digit
        alt = not alt
    
    return sum % 10 == 0


def credit():
    n = int(input("hello my name is pattel, pls give your credit card number: "))
    bad = "INVALID"

    if not is_valid_luhn(n):
        print(bad)
    else:
        str_n = str(n)
        if len(str_n) == 15 and (str_n.startswith("34") or str_n.startswith("37")):
            print("AMEX")
        elif (len(str_n) == 16 or len(str_n) == 13) and str_n.startswith("4"):
            print("VISA")
        elif len(str_n) == 16 and str_n.startswith("5") and str_n[1] in "12345":
            print("MASTERCARD")
        else:
            print(bad)

if __name__ == "__main__":
    main()