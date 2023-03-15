# TODO
from cs50 import get_int

now = True
while now:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        now = False

k = 1
for i in range(h):
    for l in range(h - 1):
        print(" ", end="")
    h -= 1
    for j in range(k):
        print("#", end="")
    k += 1
    print()