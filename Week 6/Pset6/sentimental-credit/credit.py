import sys
import re
from cs50 import get_string


def is_valid(number):
    # check if card is valid according to Luhn's algorithm
    second_to_last_sum = 0
    not_product_sum = 0
    # traverse provided card number string in reverse
    for i, c in enumerate(reversed(number)):
        # if is odd, starting from reverse. Thus getting second to last
        if i % 2 == 1:
            product = int(c) * 2
            # check if product is smaller than 10
            if product < 10:
                second_to_last_sum += product
            else:
                # if number is greater than 10,
                # add numbers of product separately
                for i in str(product):
                    second_to_last_sum += int(i)
        else:
            # sum together numebers that weren't part of the digit products
            not_product_sum += int(c)
    return (second_to_last_sum + not_product_sum) % 10 == 0


def is_amex(number):
    # check for amex card: starts with 34 or 37 and is 15 characters long
    return re.match('^(34|37)[\d]{13}$', number) and is_valid(number)


def is_mastercard(number):
    # check for mastercard card:
    # starts with 51,52,53,54 or 55 and is 16 characters long
    return re.match('^(51|52|53|54|55)\d{14}$', number) and is_valid(number)


def is_visa(number):
    # check for visa card: starts with 4 and is 13 or 16 characters long
    return re.match('^(4)(\d{12}|\d{15})$', number) and is_valid(number)


def main():
    user_number = get_string('Number: ')
    if is_amex(user_number):
        print("AMEX\n")
    elif is_mastercard(user_number):
        print("MASTERCARD\n")
    elif is_visa(user_number):
        print("VISA\n")
    else:
        print("INVALID\n")


if __name__ == "__main__":
    main()
    sys.exit(0)
