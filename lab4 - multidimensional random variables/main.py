import random
import numpy as np

#   1  2  3   4
# 0.2  0  0 0.8

#   1  2  3  4
# 1.0  0  0  0

#   1   2   3   4
#   0 0.5 0.0 0.5

#   1  2  3   4
#   0  0  1   0

nbs = [[0 for _ in range(4)] for _ in range(4)]

for i in range(4):
    for j in range(4):
        print(nbs[i][j], end=' ')
    print()

for i in range(1000000):
    x = random.random()
    y = random.random()
    x_index = 0
    y_index = 0
    if x <= 0.5:
        x_index = 1
        if y <= 0.2:
            y_index = 1
        else:
            y_index = 4
    elif x <= 0.7:
        x_index = 2
        y_index = 1
    elif x <= 0.9:
        x_index = 3
        if y <= 0.5:
            y_index = 2
        else:
            y_index = 4
    else:
        x_index = 4
        y_index = 3

    nbs[x_index - 1][y_index - 1] += 1

for i in range(4):
    for j in range(4):
        print(nbs[i][j], end='\t\t')
    print()
