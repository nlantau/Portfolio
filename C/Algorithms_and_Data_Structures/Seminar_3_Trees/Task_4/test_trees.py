# nlantau, 2021-01-03

import pytest
import cProfile
import os
from copy import deepcopy
from random import randint, sample

os.path.join(os.path.dirname(__file__), r".")

from AVL import AVLNode, AVLTree
from Heap import BinaryHeap
from RedBackTree import RBTNode, RedBlackTree
from BinarySearchTree import BSTNode, BinarySearchTree

dsa = [AVLTree, BinarySearchTree, BinaryHeap, RedBlackTree]
mock_lists = (
    [sample(range(1, 10000000), 100)]
    + [sample(range(1, 10000000), 1000)]
    # + [sample(range(1, 10000000), 10000)]
    # + [sample(range(1, 10000000), 100000)]
)


# Test remove()/delete()
def generic_dsa_load(dsa, nums):
    dsa_obj = dsa()
    for val in nums:
        dsa_obj.insert(val)
    return dsa_obj


def cProfile_test():
    # cProfile insert() 1000 elements (to profile ncalls)
    with cProfile.Profile() as pr:
        pr.run("generic_dsa_load(AVLTree, mock_lists[1])")
        pr.run("generic_dsa_load(BinarySearchTree, mock_lists[1])")
        pr.run("generic_dsa_load(BinaryHeap, mock_lists[1])")
        pr.run("generic_dsa_load(RedBlackTree, mock_lists[1])")
        pr.print_stats()


cProfile_test()


def remove_one(dsa_obj, val_to_del):
    if isinstance(dsa_obj, AVLTree):
        dsa_obj.delete(val_to_del)
    elif isinstance(dsa_obj, BinarySearchTree):
        dsa_obj.remove(val_to_del)
    elif isinstance(dsa_obj, BinaryHeap):
        dsa_obj.delete_min()
    else:
        if isinstance(dsa_obj, RedBlackTree):
            dsa_obj.delete_node(val_to_del)


@pytest.mark.parametrize("values", deepcopy(mock_lists))
@pytest.mark.parametrize("dsa_", dsa)
def test_dsa_remove(benchmark, dsa_, values):
    nums = deepcopy(values)
    dsa_obj = generic_dsa_load(dsa_, nums)
    to_del = values[len(values) // 2]

    benchmark(remove_one, dsa_obj, to_del)


# Test insert()
def generic_dsa_insert(dsa, nums):
    dsa_obj = dsa()
    for val in nums:
        dsa_obj.insert(val)


@pytest.mark.parametrize("values", deepcopy(mock_lists))
@pytest.mark.parametrize("dsa_", dsa)
def test_dsa_insert(benchmark, dsa_, values):
    nums = deepcopy(values)
    benchmark(generic_dsa_insert, dsa_, nums)