import csv
import re


counter = 0
input_title = input("Title: ").strip().upper()

with open("favorites.csv") as file:
    csv_reader = csv.DictReader(file)
    for row in csv_reader:
        title = row['title'].strip().upper()
        if title == input_title:
            counter += 1

print(f"Number of people who like {input_title}: {counter}")