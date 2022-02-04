# nlantau, 2020-12-20

import os
import rich
import copy
from sympy import *
import re
from dill.source import getsource


TABLE_SIZE = 10
SEVEN = 7
# GIVEN = [4371, 1323, 6173, 4199, 4344, 9679, 1989]
# GIVEN = [12,38,23,32,6,71,42]
GIVEN = [12, 18, 13, 2, 3, 23, 5, 15]
BOOK = [89, 18, 49, 58, 69]

CHAIN_TABLE = [[] for _ in range(TABLE_SIZE)]
LIN_PROBE_TABLE = dict.fromkeys(range(TABLE_SIZE))
QUAD_PROBE_TABLE = copy.deepcopy(LIN_PROBE_TABLE)
CHAIN_TABLE_DIC = {
    k: v for (k, v) in zip(range(TABLE_SIZE), copy.deepcopy(CHAIN_TABLE))
}


def task_2a_2e(hx, h2x, num_list):
    def create_chaining_2a(hx, num_list):
        print(f"Task 2A")
        # print hash-function used
        print_func_info(hx, num_list)

        # create new empty hash table
        table = copy.deepcopy(CHAIN_TABLE_DIC)

        # create new deepcopy of global number list to be put in hash table
        values = copy.deepcopy(num_list)

        # chain 'em!
        for i, (idx, val) in enumerate(table.items()):
            if i < len(values):
                table[hx(values[i])].append(values[i])
        print_dict(table)

    def create_task_2e(hx, h2x, num_list):
        print(f"Task 2E")
        # print hash-function used
        print_func_info(hx, num_list, h2x)

        # create new empty hash table
        table = copy.deepcopy(CHAIN_TABLE_DIC)

        # create new deepcopy of global number list to be put in hash table
        values = copy.deepcopy(num_list)

        # h(x) and h2(x)
        for i, (idx, val) in enumerate(table.items()):
            if i < len(values):
                index = hx(values[i])
                if len(table[index]) < 1:
                    table[index].append(values[i])
                else:
                    while len(table[index]) == 1:
                        index += h2x(values[i])
                        index %= TABLE_SIZE
                    table[index].append(values[i])
        print_dict(table)

    def create_task_2f(hx, h2x, num_list):
        print(f"Task 2F")
        # print hash-function used
        print_func_info(hx, num_list, h2x)

        # create new empty hash table
        table = {
            k: v
            for (k, v) in zip(
                range(TABLE_SIZE * 2), [[] for _ in range(TABLE_SIZE * 2)]
            )
        }

        # create new deepcopy of global number list to be put in hash table
        values = copy.deepcopy(num_list)

        # h(x) and h2(x)
        for i, (idx, val) in enumerate(table.items()):
            if i < len(values):
                index = hx(values[i])
                if len(table[index]) < 1:
                    table[index].append(values[i])
                else:
                    while len(table[index]) == 1:
                        index += h2x(values[i])
                        index %= TABLE_SIZE
                    table[index].append(values[i])
        print_dict(table)

    # Call inner functions
    create_chaining_2a(hx, num_list)
    if isprime(TABLE_SIZE):
        create_task_2e(hx, h2x, num_list)
        create_task_2f(hx, h2x, num_list)


def task_2b(hx, rhx, num_list):
    def create_linear_probe(hx, rhx, num_list):
        print(f"Task 2B")
        # print hash-function used
        print_func_info(hx, num_list, rhx)

        # create new empty hash table
        table = copy.deepcopy(LIN_PROBE_TABLE)

        # create new deepcopy of global number list to be put in hash table
        values = copy.deepcopy(num_list)
        for i, (idx, val) in enumerate(table.items()):
            if i < len(values):
                index = hx(values[i])
                if table[index] == None:
                    table[index] = values[i]
                else:
                    y = 0
                    while table[index] is not None:
                        # print("Collision")
                        index = rhx(index, y)
                        y += 1
                    table[index] = values[i]

        print_dict(table)

    create_linear_probe(hx, rhx, num_list)


def task_2c(hx, qrhx, num_list):
    def quad_linear_probe(hx, qrhx, num_list):
        print(f"Task 2C")
        # print hash-function used
        print_func_info(hx, num_list, qrhx)

        # create new empty hash table
        table = copy.deepcopy(QUAD_PROBE_TABLE)

        # create new deepcopy of global number list to be put in hash table
        values = copy.deepcopy(num_list)
        for i, (idx, val) in enumerate(table.items()):
            if i < len(values):
                index = hx(values[i])
                if table[index] == None:
                    table[index] = values[i]
                else:
                    y = 0
                    while table[index] is not None:
                        # print("Collision")
                        index = qrhx(index, y)
                        y += 1
                    table[index] = values[i]

        print_dict(table)

    quad_linear_probe(hx, qrhx, num_list)


def hash_div(k):
    return k % TABLE_SIZE


def hash_mod_7(k):
    return SEVEN - (k % SEVEN)


def quad_rehash(oldhash, y):
    return (oldhash + y * y) % TABLE_SIZE


def rehash(oldhash, y):
    return (oldhash + y) % TABLE_SIZE


def print_dict(dic):
    print()
    for k, v in dic.items():
        print(f"{k:>2} : {v}")
    print()


def print_func_info(fx, num_list, gx=0):
    re_bod = re.compile(r"(?<=return\s)(?P<state>(.*))")
    fn_bod = getsource(fx)
    ret_st = re_bod.search(fn_bod)
    print(f"h(x): {fx.__name__:<12} returning: {ret_st.group('state')}")
    if gx != 0:
        fn2_bod = getsource(gx)
        ret2_st = re_bod.search(fn2_bod)
        print(f"g(x): {gx.__name__:<12} returning: {ret2_st.group('state')}")
    print(f"List: {num_list}")


if __name__ == "__main__":
    if os.uname().sysname == "Darwin":
        os.system("clear")
    else:
        os.system("cls")
    print(f"\n\n{' NEW ROUND ':-^30}\n")
    task_2a_2e(hash_div, hash_mod_7, GIVEN)
    task_2b(hash_div, rehash, GIVEN)
    task_2c(hash_div, quad_rehash, GIVEN)