# TODO
from cs50 import get_float

now = True
while now:
    change = get_float("Change owed: ")
    if change > 0:
        now = False

i = 0
change *= 100

while change >= 25:
    change -= 25
    i += 1

while change >= 10:
    change -= 10
    i += 1

while change >= 5:
    change -= 5
    i += 1

while change >= 1:
    change -= 1
    i += 1

print(f"{i}")