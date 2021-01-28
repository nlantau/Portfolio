# nlantau, 2020-06-24
"""Timer decorator"""

import time
from functools import wraps



def timer(func):
    """ Timer decorator """

    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        value = func(*args, **kwargs)
        stop = time.perf_counter() - start
        print(f'\nElapsed time for executing function {func.__name__!r}:')
        print(f'{stop:.6f} seconds\n')
        return value

    return wrapper


if __name__ == "__main__":

    @timer
    def tester(name):
        print(f"hej {name}")

    tester("Niklas")
