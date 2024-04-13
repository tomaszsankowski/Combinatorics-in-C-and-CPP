import random


# rand z zakresem liczb rzeczywistych
# rand gdzie niektorze eleemnty pojawiaja sie czesciej od innych

def exercise2():
    nbs = [0]*4
    for i in range(1000000):
        x = random.random()
        if x <= 0.2:
            nbs[0] += 1
        elif x <= 0.6:
            nbs[1] += 1
        elif x <= 0.9:
            nbs[2] += 1
        else:
            nbs[3] += 1

    for i in range(len(nbs)):
        print((i+1), ': ', nbs[i])


# funkcja Fun jest pochodną funkcji 1/100
# y = (x-50)*(1/100)
# 100y = x - 50
# x = 100y + 50
def Fun(x): # funkcja 1/100 * x
    return 1/100*x


def exercise1():
    przedzialy = [0]*10
    for i in range(1000000):
        y = random.random()
        num = 100*y+50
        for j in range(10):
            if 50.0+j*10 < num <= 60.0+j*10:
                przedzialy[j] += 1
                break

    for i in range(10):
        print('[ ', (50+i*10), ' - ', (60+i*10), ' ]: ', przedzialy[i])


exercise1()
print()
exercise2()
