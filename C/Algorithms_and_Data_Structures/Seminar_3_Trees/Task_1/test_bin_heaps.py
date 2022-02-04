# nlantau, 2021-01-01

import pytest
import cProfile
import os
from copy import deepcopy
from random import randint, sample

os.path.join(os.path.dirname(__file__), r".")
from binary_heap import BinaryHeap
from main import create_heap_for_loop_insert


mock_lists = (
    [sample(range(1, 10000000), 100)]
    + [sample(range(1, 10000000), 1000)]
    + [sample(range(1, 10000000), 10000)]
    + [sample(range(1, 10000000), 100000)]
    + [sample(range(1, 10000000), 200000)]
    + [sample(range(1, 10000000), 400000)]
    + [sample(range(1, 10000000), 600000)]
    + [sample(range(1, 10000000), 800000)]
    + [sample(range(1, 12000000), 1000000)]
)

dsa = [BinaryHeap]


def generic_dsa_insert(dsa, nums):
    dsa_obj = dsa()
    for val in nums:
        dsa_obj.insert(val)


def generic_dsa_load(dsa, nums):
    dsa_obj = dsa()
    for val in nums:
        dsa_obj.insert(val)
    return dsa_obj


def test_heap_build():
    bh_bh = BinaryHeap()
    bh_bh.build_heap(mock_lists[1])
    return bh_bh


def test_heap_for():
    bh_in = generic_dsa_load(BinaryHeap, mock_lists[1])
    return bh_in


def test_delete_min(bh_in):
    bh_in.delete_min()


def test_insert_one(bh_in):
    bh_in.insert(100)


# Global BinaryHeap() for easier access between test
# Contain 1000 elements
bh_bh = test_heap_build()
bh_in = test_heap_for()


def cProfile_test():
    # cProfile insert() 1000 elements (to profile ncalls)

    with cProfile.Profile() as pr:
        # pr.run("test_heap_build()")
        # pr.run("test_heap_for()")
        # pr.run("test_delete_min(bh_in)")
        # pr.run("test_delete_min(bh_bh)")
        pr.run("test_insert_one(bh_bh)")
        pr.print_stats()


# print("> Test Expense BinaryHeap() inserting 1000 unique values")
print("> Test Expense BinaryHeap() insert one number into obj ")
print("> containing 1000 unique values")
print("> using 'algorithm 2' ")
cProfile_test()
"""
@pytest.mark.parametrize("dsa_", dsa)
@pytest.mark.parametrize("values", mock_lists)
def test_heap_insert(benchmark, dsa_, values):
    nums = deepcopy(values)
    benchmark(generic_dsa_insert, dsa_, nums)


@pytest.mark.parametrize("dsa_", dsa)
@pytest.mark.parametrize("values", mock_lists)
def test_heap_build_heap(benchmark, dsa_, values):
    nums = deepcopy(values)
    benchmark(dsa_().build_heap, nums)

"""


@pytest.mark.parametrize("values", deepcopy(mock_lists))
@pytest.mark.parametrize("dsa_", dsa)
def test_heap_delete_min_insert(benchmark, dsa_, values):
    nums = deepcopy(values)
    dsa_obj = generic_dsa_load(dsa_, nums)
    to_del = values[len(values) // 2]

    benchmark(dsa_obj.delete_min)


@pytest.mark.parametrize("values", deepcopy(mock_lists))
@pytest.mark.parametrize("dsa_", dsa)
def test_heap_delete_min_build_heap(benchmark, dsa_, values):
    nums = deepcopy(values)
    dsa_obj = BinaryHeap()
    dsa_obj.build_heap(values)
    to_del = values[len(values) // 2]

    benchmark(dsa_obj.delete_min)