from functools import lru_cache
import timeit
import sys
import cProfile


def rec_sub(n, a):
    if n < 1:
        return
    print("n2:", n)
    a.append(n)
    rec_sub(n - 1, a)
    a.append(n)
    return a


def fact(n):
    if n == 0:
        return 1
    return n * fact(n - 1)


def reverse_str(s):

    if len(s) == 1:
        return s

    return reverse_str(s[1:]) + s[0]


def perm_str(s):
    print(f"s: {s}")
    out = []
    if len(s) <= 1:
        out = [s]
    else:
        for i, ch in enumerate(s):
            print(f"For ch {ch} and i {i} perm_str(s[{s[:i]}] + s[{s[i+1:]}])\n")
            for perm in perm_str(s[:i] + s[i + 1 :]):
                print(f"out {out} += [{ch} + {perm}] ")
                out += [ch + perm]
                print(f"out {out}")
            print("------>")
    return out


def rec_num(i: list):

    if len(i) == 1:
        print(f"i: {i}")
        return i

    else:
        mid = len(i) // 2
        first = i[:mid]
        second = i[mid:]
        rec_num(first)
        rec_num(second)


@lru_cache
def fib_lru(n):
    if n == 0 or n == 1:
        return 1
    else:
        return fib_lru(n - 1) + fib_lru(n - 2)


def fib_std(n):
    if n == 0 or n == 1:
        return 1
    else:
        return fib_std(n - 1) + fib_std(n - 2)


def fib_memo(n, mem_arr):
    if n in mem_arr:
        return mem_arr[n]
    else:
        mem_arr[n] = fib_memo(n - 2, mem_arr) + fib_memo(n - 1, mem_arr)
    return mem_arr[n]


def time_fib_std():
    return fib_std(30)


def time_fib_lru():
    return fib_lru(3000)


def time_fib_memo():
    return fib_memo(3000, {0: 0, 1: 1})


def iter_mul_el_by_2(n):
    new_n = []
    for num in n:
        new_n.append(num * 2)
    return new_n


def rec_mul_el_by_2(n):
    if len(n) < 1:
        return []
    return [n[0] * 2] + rec_mul_el_by_2(n[1:])
    # return [chr(n[0] + 65)] + rec_mul_el_by_2(n[1:])


if __name__ == "__main__":
    # print(fib_memo(10, {0: 0, 1: 1}))

    """
    nums = [_ for _ in range(10)]
    print(iter_mul_el_by_2(nums))
    print(rec_mul_el_by_2(nums))
    """

    sys.setrecursionlimit(100000)
    print(f"LRU  :{timeit.timeit(time_fib_lru, number=1)} seconds")
    print(f"Std  :{timeit.timeit(time_fib_std, number=1)} seconds")
    print(f"Memo :{timeit.timeit(time_fib_memo, number=1)} seconds")

    """
    cProfile.run("fib_lru(3000)")
    cProfile.run("fib_std(30)")
    cProfile.run("fib_memo(3000, {0:0,1:1})")
    a = list()
    y = rec_sub(10, a)
    print(y)
    print(fact(4))
    print(reverse_str("abc"))
    print(perm_str("abc"))
    rec_num([_ for _ in range(10)])
    """

