# nlantau, 2021-01-02

import pytest
import cProfile
import os
from copy import deepcopy
from random import randint

os.path.join(os.path.dirname(__file__), r".")
from main import TABLE_SIZE, GIVEN, SEVEN, hash_div, hash_mod_7, quad_rehash, rehash

first_funcs = [hash_div, hash_mod_7]
first_values = [randint(1, 1000000) for _ in range(1)]
second_funcs = [quad_rehash, rehash]
second_values = [randint(1, 1000000) for _ in range(1)]
second_oldhash_mock = [11]


@pytest.mark.parametrize("func", deepcopy(first_funcs))
@pytest.mark.parametrize("val", first_values)
def test_div_seven(benchmark, func, val):
    benchmark(func, val)


@pytest.mark.parametrize("func", second_funcs)
@pytest.mark.parametrize("val", second_values)
@pytest.mark.parametrize("old_hash_mock", second_oldhash_mock)
def test_quad_rehash(benchmark, func, val, old_hash_mock):
    benchmark(func, val, old_hash_mock)