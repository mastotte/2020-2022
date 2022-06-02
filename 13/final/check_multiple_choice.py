#!/usr/bin/env python3

answers = {}

try:
    with open("answers.txt") as infile:
        for line in infile:
            num, answer = line.strip().split(": ")
            num = int(num)
            answers[num] = answer

    print("found these answers:", answers)

    error = False
    for num in range(1, 16):
        if num not in answers:
            print("WARNING NO ANSWER FOR MULTIPLE CHOICE {}".format(num))
            error = True
        elif answers[num] not in "abcdABCD":
            print("need an answer A|B|C|D for question: {}".format(num))
            error = True

    if error:
        print("answers.txt is not complete.")
    else:
        print("every question in answers.txt has been answered!")
except:
    print("could not parse answers.txt, this is no good!")
