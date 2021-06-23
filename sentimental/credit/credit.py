import cs50


def luhn(to_check):
    times_two = 0
    times_one = 0
    product = 0

    while to_check:
        times_one += to_check % 10
        to_check //= 10

        # Check at least one digit left
        if to_check:
            product = (to_check % 10) * 2

            while product:
                times_two += product % 10
                product //= 10

            to_check //= 10

    return (times_two + times_one) % 10 == 0


number = cs50.get_int("Number: ")

if not luhn(number):
    print("INVALID")
else:
    # Go through the other conditions
    if len(str(number)) == 15 and int(str(number)[:2]) in [34, 37]:
        print("AMEX")
    elif len(str(number)) == 16 and int(str(number)[:2]) in [51, 52, 53, 54, 55]:
        print("MASTERCARD")
    elif len(str(number)) in [13, 16] and int(str(number)[:1]) in [4]:
        print("VISA")
    else:
        print("INVALID")
