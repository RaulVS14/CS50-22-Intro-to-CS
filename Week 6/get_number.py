def get_number(msg):
    valid_number = False
    while not valid_number:
        try:
            points = int(input(msg))
            if points < 0:
                print("Must be positive number!\n")
            else:
                return points
        except ValueError:
            print("That is not a number!")
