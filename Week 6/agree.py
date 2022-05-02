s = input("Do you agree? (Y/N)\n").lower()

if s in ["y", "yes"]:
    print("Agreed.\n")
elif s in ["n", "no"]:
    print("Not agreed.\n")
else:
    print("Not sure about your answer.\n")