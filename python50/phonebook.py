import csv

with open("phonebook.csv", "a") as file:
    input_name = input("Name: ")
    input_number = input("Number: ")

    writer = csv.writer(file)
    writer.writerow([input_name, input_number])