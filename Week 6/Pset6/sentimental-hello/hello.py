import sys


def greeting(name):
    # Return string and capitalize in case user doesn't
    return f"hello, {name.capitalize()}"


def main():
    # Ask user for name
    name = input("What is your name?\n")

    # Print out the greeting with name
    print(greeting(name))


if __name__ == "__main__":
    main()
    sys.exit(0)