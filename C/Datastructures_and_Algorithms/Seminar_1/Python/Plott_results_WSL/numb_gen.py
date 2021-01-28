# nlantau, 2020-11-17
"""
This module will generate a textfile with random ordered numbers,
where 0 <= n <= 2 x 10^7.

This is to test sorting algorithms harder
"""

import sys
import os
import random


path = r"/mnt/c/Github/DT256CHT20/"
txtf = r"90K.txt"
itr_ = 90000


def generate_numbfile(path: str):
    try:
        with open(path + txtf, "a") as creator:
            for _ in range(itr_):
                creator.write(str(random.randint(0, 20000000)) + "\n")
    except FileNotFoundError as e:
        print("> File not found", file=sys.stderr)


def main(path: str):
    generate_numbfile(path)


if __name__ == "__main__":
    main(path)
