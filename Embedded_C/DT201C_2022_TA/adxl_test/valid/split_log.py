#!/usr/bin/env python3
# nlantau, 2021-05-18

FILENAME = r'data.log'

n_1 = list()
n_25 = list()
n_50 = list()
n_75 = list()
n_100 = list()

def reader(li, st):
    while (d := r.readline().strip()) != st:
        li.append(d)
        print(f'{d}')

def saver(li, path):
    with open(path, 'w') as w:
        for line in li:
            w.writelines(line + '\n')


with open(FILENAME, 'r') as r:
    reader(n_1, "NEXT")
    reader(n_25, "NEXT")
    reader(n_50, "NEXT")
    reader(n_75, "NEXT")
    reader(n_100, "DONE")

saver(n_1, "n1.csv")
saver(n_25, "n25.csv")
saver(n_50, "n50.csv")
saver(n_75, "n75.csv")
saver(n_100, "n100.csv")


