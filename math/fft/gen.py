import os, sys
from random import randint
_, N = sys.argv
N = int(N)
Q = N

while N > 0:
    print(randint(0, 10)%10,end="")
    N -= 1
print()
while Q > 0:
    print(randint(0, 10)%10,end="")
    Q -= 1