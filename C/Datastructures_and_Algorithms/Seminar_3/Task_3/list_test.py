import pytest
import numpy as np
import numba


class Num:
    def __init__(self, i):
        self.i = i

    def __add__(self, x):
        return Num(self.i + x.i)


t_string = "Num(1) + Num(2) + Num(3)"
s = eval(t_string).i
# s = Num(1).i
print(s)


t_bone = "1: 4 1 5"
rule, val = t_bone.split(": ")
print(rule)
print(val)


x = np.arange(100).reshape(10, 10)
y = [x for x in range(10)]
# print(x)
# print(y)


def gen_arr_np_arange():
    x = [np.cos(i) for i in np.arange(10)]
    return x


def gen_arr_range():
    pass


# print(gen_arr_np_arange())


@numba.njit
def loop_as_hell_numba():
    sum = 0
    for i in range(1000):
        for j in range(1000):
            for k in range(100):
                sum += 2
    return sum


def loop_as_hell_python():
    sum = 0
    for i in range(1000):
        for j in range(1000):
            for k in range(100):
                sum += 2
    return sum


def test_loop_python(benchmark):
    benchmark(loop_as_hell_python)


def test_loop_numba(benchmark):
    benchmark(loop_as_hell_numba)
