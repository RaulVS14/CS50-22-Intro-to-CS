try:
    x = int(input("x: "))
except ValueError:
    print("That is not a number!")
    exit()
try:
    y = int(input("y: "))
except ValueError:
    print("That is not a number!")
    exit()

z = x / y
print(f"{z:.50f}")