try:
    points = int(input("how many points did you lose: "))
except ValueError:
    print("That is not a number!")
    exit()
if points < 2:
    print("You lost fewer points than me.\n")
elif points > 2:
    print("You lost more points than me.\n")
else:
    print("You lost the same number of points as me.\n")