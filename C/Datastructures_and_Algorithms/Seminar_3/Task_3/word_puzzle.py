# nlantau, 2020-12-20

import pytest
from os import path, system
from time import sleep
from sympy import isprime
from copy import deepcopy
from random import randint
import re

path.join(path.dirname(__file__), r".")
fin = path.join(path.dirname(__file__), r"word_list.txt")

from cell_coord import Coordinate, Neighbor, Cell

TABLE_SIZE = 5987


def read_file() -> dict:
    chain = [[] for _ in range(TABLE_SIZE)]
    dic = {k: v for (k, v) in zip(range(TABLE_SIZE), deepcopy(chain))}

    with open(fin, "r") as r:
        data = r.read().split()

        for i, word in enumerate(data):
            dic[hash_all_letters(word)].append(word)
    return dic


def hash_all_letters(word) -> int:
    x = 0
    for ch in word:
        ascii_val = ord(ch)
        x += ascii_val
    return x % TABLE_SIZE


def create_2D_array(x=4, y=4) -> list:
    puz = list()
    inner_puz = list()

    for i in range(x):
        inner_puz.clear()
        for k in range(y):
            letter = chr(randint(97, 122))
            inner_puz.append(letter)
        puz.append(deepcopy(inner_puz))
    return puz


def search_board(hashed_dict, puzzle_input, x=4, y=4) -> set and dict:
    list_of_grid_cells = list()
    matched_words = set()

    chain = [[] for _ in range(TABLE_SIZE)]
    all_comb_dict = {k: v for (k, v) in zip(range(TABLE_SIZE), deepcopy(chain))}

    # Add a Cell to each position O(N^2)
    for i in range(x):
        for j in range(y):
            list_of_grid_cells.append(Cell(i, j, max_x=x, max_y=y))

    # Check each Cell. O(N^4) ?
    for cell in list_of_grid_cells:
        for nabo in cell.valid_neighbors:
            for pos in nabo:
                s_b = list()
                for one in pos:
                    s_b.append(puzzle_input[one[0]][one[1]])
                word = "".join([x for x in s_b])
                all_comb_dict[hash_all_letters(word)].append(word)

    # Check words in all_combinations agains real words! O(N^3)
    for k, v in hashed_dict.items():
        if len(v) >= 1:
            for val in v:
                hv = hash_all_letters(val)  # Stupid
                for word in all_comb_dict[hv]:
                    if val == word:
                        matched_words.add(val)

    return matched_words, all_comb_dict


def run():
    hashed_dict = read_file()
    while True:
        system("clear")
        row, col = user_grid_size_input()
        puz = create_2D_array(x=row, y=col)

        display_board(puz)
        words_found, all_combs = search_board(hashed_dict, puz, x=row, y=col)
        u_str = user_search_string_input()
        if "ZZ" in u_str:
            system("clear")
            print("Bye..")
            sleep(1.5)
            system("clear")
            raise SystemExit
        hashed_u_str = hash_all_letters(u_str.lower())
        possible_matches = all_combs[hashed_u_str]
        if u_str in possible_matches:
            print(f"\nMatch! {u_str} found in puzzle")
            if len(words_found) > 1:
                print("\nHere's all matches:")
                print(*words_found, sep=", ")
            print()
            ignore_me = input("> Press Enter to continue...")
        else:
            print("No match, mate")
            sleep(1.5)


def user_search_string_input() -> str:
    u_pat = re.compile(r"(?P<str>[a-zA-Z]+)")
    print("> Enter 'ZZ' to exit")
    while True:
        inp = input("> Enter search string: (non-digit) ")
        try:
            res = u_pat.search(inp)
            s_str = res.group("str")
            return s_str
        except AttributeError:
            print("> Try again...")


def user_grid_size_input() -> int and int:
    u_pat = re.compile(r"(?P<num_one>\d{1,2})(?:\D+)(?P<num_two>\d{1,2})")
    while True:
        inp = input("> Enter size: (num x num) ")
        try:
            res = u_pat.search(inp)
            num_one = res.group("num_one")
            num_two = res.group("num_two")
            return int(num_one), int(num_two)
        except AttributeError:
            print("> Try again...")


def print_dic(dic):
    for idx, val in dic.items():
        if len(val) >= 1:
            print(f"{idx:>3} : {val}")


def print_primes():
    for i in range(5000, 6000):
        if isprime(i):
            print(i)


def display_board(puzzle_input):
    for i, word in enumerate(puzzle_input):
        print("", *word, sep="  ")
    print()


def test_read_file_and_hash_all_words(benchmark):
    benchmark(read_file)


def test_sleep_0_001sec(benchmark):
    benchmark(sleep, 0.001)


def test_hash_one_word(benchmark):
    benchmark(hash_all_letters, "sophisticated")


def test_search_board(benchmark):
    hashed_dict = read_file()
    row, col = 10, 10
    puz = create_2D_array(x=row, y=col)
    benchmark(search_board, hashed_dict, puz, x=row, y=col)


if __name__ == "__main__":
    run()
    # print_primes()
    # print_dic(all_combs)
