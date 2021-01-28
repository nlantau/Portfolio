from functools import *
from itertools import *
from collections import *
import os, sys, re
import heapq as hq
import random
import math
from binarytree import heap, build
import timeit
import cProfile

os.path.join(os.path.dirname(__file__), r".")
from bin_heap import BinHeap


def test_my_own_binary_heap(list_one) -> [int]:
    bh = BinHeap()
    # x = [random.randint(2, 100) for _ in range(10)]
    x = list_one
    print("In :", *x)
    for i in x:
        bh.insert(i)
    print("Out:", end=" ")
    while bh.currentSize > 0:
        print(bh.delMin(), end=" ")
    print()
    return x


def test_binary_tree_module(values):

    # Build a tree from list representation
    root = build(values)
    print(root)
    #print_root(root)


def print_root(root):
    print(f"root.inorder   : {root.inorder}")
    print(f"root.preorder  : {root.preorder}")
    print(f"root.postorder : {root.postorder}")
    print(f"root.levelorder: {root.levelorder}")


"""
more itertools
itertools
collections
eval, map, reduce, lamdba
"""
if __name__ == "__main__":
    t1_list = [10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4, 11, 13, 2]
    values = test_my_own_binary_heap(t1_list)
    test_binary_tree_module(t1_list)
    # print(f"{timeit.timeit(test_binary_tree_module, number=1)}")
    # cProfile.run("test_binary_tree_module()")
