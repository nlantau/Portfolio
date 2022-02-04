# nlantau, 2020-12-15
import os
import sys
import re
from copy import deepcopy
from random import randint
import timeit
import cProfile
from rich.console import Console
from rich.table import Table
from binarytree import *

os.path.join(os.path.dirname(__file__), r".")
from binary_heap import BinaryHeap

TASK_ONE_A = [10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4, 11, 13, 2]
# TASK_ONE_A = [x for x in range(10)]


def print_pretty_tree(unsorted_list):
    root = build(unsorted_list)
    print(root)


def level_order(bh):
    # Works fine
    x = f"{'Level order':<15}"
    return x, bh.level_order_traversal()


def min_to_max(bh):
    # Works fine
    print(f"{'Min-max order':<15}:", end=" ")
    while bh.currentSize > 0:
        print(bh.delete_min(), end=" ")
    print()


def travers_tree_inorder(bh):
    # Works fine
    x = f"{'Inorder walk':<15}"
    return x, bh.inorder_tree_walk(1, [])


def travers_tree_preorder(bh):
    # Works fine
    x = f"{'Preorder walk':<15}"
    return x, bh.preorder_tree_walk(1, [])


def travers_tree_postorder(bh):
    # Works fine
    x = f"{'Postorder walk':<15}"
    return x, bh.postorder_tree_walk(1, [])


def create_heap_for_loop_insert(unsorted_list):
    bh = BinaryHeap()
    for num in unsorted_list:
        bh.insert(num)
    x = f"{'Heap list ':<15}"
    return x, bh


def task_1ab():
    task_list = deepcopy(TASK_ONE_A)

    _, bh_obj = create_heap_for_loop_insert(task_list)  # for-loop, insert()
    bh_linear = BinaryHeap()  # New bh-obj for linear insertion
    bh_linear.build_heap(task_list)  # Build with linear insertion

    # HeapList
    bh_list = ", ".join([str(l) for l in bh_obj.heapList[1::]])
    bh_linear_list = ", ".join([str(l) for l in bh_linear.heapList[1::]])

    # "For-loop"-obj walks
    xa, a = travers_tree_inorder(bh_obj)
    xb, b = travers_tree_postorder(bh_obj)
    xc, c = travers_tree_preorder(bh_obj)
    xd, d = level_order(bh_obj)

    # "Linear"-obj walks
    ignore, aa = travers_tree_inorder(bh_linear)
    ignore, bb = travers_tree_postorder(bh_linear)
    ignore, cc = travers_tree_preorder(bh_linear)
    ignore, dd = level_order(bh_linear)

    table = Table("Task", "Array", "Insert Method")

    table.add_row("1a, algorithm 1", bh_list, "for-loop")
    table.add_row("1b, algorithm 2", bh_linear_list, "Linear")

    table.add_row("", "", "")
    table.add_row("1c, " + xa, ", ".join([str(l) for l in a]), "for-loop")
    table.add_row("1c, " + xb, ", ".join([str(l) for l in b]), "for-loop")
    table.add_row("1c, " + xc, ", ".join([str(l) for l in c]), "for-loop")
    table.add_row("1c, " + xd, ", ".join([str(l) for l in d]), "for-loop")
    table.add_row("", "", "")
    table.add_row("1c, " + xa, ", ".join([str(l) for l in aa]), "Linear")
    table.add_row("1c, " + xb, ", ".join([str(l) for l in bb]), "Linear")
    table.add_row("1c, " + xc, ", ".join([str(l) for l in cc]), "Linear")
    table.add_row("1c, " + xd, ", ".join([str(l) for l in dd]), "Linear")

    console = Console()
    console.print(table)


def main():
    # task_1()
    task_1ab()


if __name__ == "__main__":
    os.system("clear")
    print()
    print(f"Execution time {timeit.timeit(main, number=1):.6f} seconds")
    # cProfile.run("main()")