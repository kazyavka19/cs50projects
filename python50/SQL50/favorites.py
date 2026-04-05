import csv
from cs50 import SQL



def count_languages(csv_path):
    counts = {}

    with open(csv_path, "r", newline="", encoding="utf-8") as file:
        reader = csv.DictReader(file)

        for row in reader:
            favorite = row["language"]
            counts[favorite] = counts.get(favorite, 0) + 1

    for favorite in sorted(counts, key=counts.get, reverse=True):
        print(f"{favorite}: {counts[favorite]}")

    return counts

def count_favorites(db):
    favorite = input("What is your favorite programming language? ")

    row = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE language = ?", favorite)
    row = row[0]

    print(row["n"])



def main():
    #count_languages("favorites.csv")
    count_favorites(SQL("sqlite:///favorites.db"))



if __name__ == "__main__":
    main()