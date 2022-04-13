from threading import *

g = 0

def f1():
    global g
#    for n in range(100000):
    g = g + 1
    return g

def f2():
    return f1() + 1

print (g)
for n in range(100000):
    thread_1 = Thread(target=f2)
    thread_1.start()

print (g)
