import sys

names = ["Alex", "Bill", "Charlie","David","Edward", "Francis","George"]

if "David" in names:
    print("FOUND")
    sys.exit(0)

print("Not Found")
sys.exit(1)