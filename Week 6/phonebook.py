phonebook = {
    "Carter":"+1-617-495-1000",
    "David":"+1-949-468-2750",
}

name = input("Name: ")

if name in phonebook:
    print(f"Number: {phonebook[name]}")