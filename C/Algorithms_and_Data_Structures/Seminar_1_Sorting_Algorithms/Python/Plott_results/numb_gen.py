# nlantau, 2020-11-17
"""
This module will generate a textfile with random ordered numbers,
where 0 <= n <= 2 x 10^7.

This is to test sorting algorithms harder
"""

import sys
import os
import random


path = r"/Users/nlantau/Docs/GitHub/DT256CHT20/Seminar_1/numb_files/"
txtf = r"10M.txt"
itr_ = 10000000


def generate_numbfile(path: str):
    try:
        with open(path + txtf, "w") as creator:
            for _ in range(itr_ - 1):
                creator.write(str(random.randint(0, 20000000)) + "\n")
            creator.write(str(12345678))  # For testing Binary Search
    except FileNotFoundError as e:
        print("> File not found", file=sys.stderr)


def main(path: str):
    generate_numbfile(path)


if __name__ == "__main__":
    main(path)
