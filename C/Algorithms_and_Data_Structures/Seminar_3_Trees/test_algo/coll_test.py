import functools as ft
import itertools as it
import collections as ct
import os, sys, re
import heapq as hq
import random
import math

os.path.join(os.path.dirname(__file__), r".")


def coll_():
    """ Test collections """
    # ni = list(map(lambda x: x * random.randint(10, 100) + 1, range(10)))
    ni = list(map(lambda x: x, range(10)))
    print(ni)
    ni = ct.Counter(ni)
    print(ni)
    ni.subtract({3: 1})
    ni.subtract({3: 1})
    print(ni)


def order_dic():
    """ Test OrderedDict """
    ni = list(map(lambda x: x // 2 + 3, range(10)))
    c = ct.Counter(ni)
    ni = ct.OrderedDict(c.most_common())
    print(*([k, v] for (k, v) in ni.items()))


def itert_():
    """ Test itertools """
    x = [1, 2, 3, 4]
    y = ["a", "b", "d"]
    z = x + y
    h = ct.ChainMap(x, y)
    print(z)
    print(h)


def named_tup():
    coord = ct.namedtuple("coord", "x y")
    ni = coord(1, 2)
    print(ni.x)
    print(ni)


def main():
    # coll_()
    order_dic()
    itert_()
    named_tup()


if __name__ == "__main__":
    main()