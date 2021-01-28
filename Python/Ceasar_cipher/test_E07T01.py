# nlantau, 2020-07-12
""" Performance test for Exercise 7 """

import cProfile
import numpy as np
from timer import timer
from E07T01 import encrypt_msg, decrypt_msg, read_txt_file, get_offset
from E07T03_plot import create_x_y_values


@timer
def performance_encrypt_msg(msg, offset):
    cProfile.run("encrypt_msg(msg, offset)")


@timer
def performance_create_dict_range():
    cProfile.run("create_dict")


@timer
def performance_create_dict_numpy():
    cProfile.run("create_dict_numpy")


@timer
def create_dict_numpy():
    return {
        k: v
        for (k, v) in zip(
            [chr(97 + k) for k in np.arange(26)],
            [[0 for x in np.arange(200)] for x in np.arange(26)],
        )
    }


@timer
def create_dict_range():
    return {
        k: v
        for (k, v) in zip(
            [chr(97 + k) for k in range(26)],
            [[0 for x in range(200)] for x in range(26)],
        )
    }


if __name__ == "__main__":
    msg = read_txt_file("freq.txt")
    perf_file = "performance_test.txt"
    # offset = get_offset()
    offset = 2

    # cProfile
    performance_encrypt_msg(msg, offset)
    # performance_create_dict_range()
    # performance_create_dict_numpy()

    # for _ in range(5):
    #    create_dict_range()
    #    create_dict_numpy()
    #    print(f'{OKBLUE}{"-":-^60}{ENDC}')
#
# for _ in range(5):
#    create_dict_numpy()
#    create_dict_range()
#    print(f'{OKGREEN}{"-":-^60}{ENDC}')
#
