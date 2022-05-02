from get_number import get_number

scores = []

for i in range(3):
    scores += [get_number(f"{i + 1}. number: ")]

average = sum(scores) / len(scores)

print(f"Average: {average}")