# nlantau, 2020-06-24
"""Timer decorator"""

import time
from functools import wraps


# Colorize text
HEADER = "\033[95m"
OKBLUE = "\033[94m"
OKGREEN = "\033[92m"
WARNING = "\033[93m"
FAIL = "\033[91m"
ENDC = "\033[0m"
BOLD = "\033[1m"
UNDERLINE = "\033[4m"


def timer(func):
    """ Timer decorator """

    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        value = func(*args, **kwargs)
        stop = time.perf_counter() - start
        print(f'\nElapsed time for executing function {func.__name__!r}:')
        #print(f'{WARNING}{stop:.6f} seconds\n{ENDC}')
        print(f'{stop:.6f} seconds\n')
        return value

    return wrapper


if __name__ == "__main__":

    @timer
    def tester(name):
        print(f"hej {name}")

    tester("Niklas")
