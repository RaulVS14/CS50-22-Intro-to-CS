import csv

titles = {}

with open("favorites.csv") as file:
    csv_reader = csv.DictReader(file)
    for row in csv_reader:
        title = row['title'].strip().upper()
        if title not in titles:
            titles[title] = 0
        titles[title] += 1

for title in sorted(titles, key=lambda title: titles[title], reverse=True):
    print(title, titles[title])