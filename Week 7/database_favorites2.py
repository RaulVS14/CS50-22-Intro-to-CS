import csv
from cs50 import SQL

db = SQL("sqlite:///favorites.db")

title = input("Title: ").strip()

rows = db.execute("SELECT COUNT(*) AS total FROM shows WHERE title LIKE ?", f"%{title}%")
row = rows[0]
print(row["total"])