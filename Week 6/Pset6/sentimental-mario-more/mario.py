import sys
from cs50 import get_int

PYRAMID_CHAR = "#"


def get_user_number():
    num = -1
    # prompt for number and check if number is in range
    while num < 1 or num > 8:
        num = get_int('Insert height of pyramid (1-8):\n')
    return num


def main():
    # Ask user for height
    height = get_user_number()

    # Build pyramid
    for i in range(height):
        pyramid_row = PYRAMID_CHAR * (i + 1)
        row_string = f'{" " * (height - (i + 1))}{pyramid_row}  {pyramid_row}'
        print(row_string)


if __name__ == "__main__":
    main()
    sys.exit(0)
