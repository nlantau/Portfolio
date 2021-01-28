# nlantau, 2020-11-15
"""
Exercises 20.6
Task 1
Using Euler's method estimate y(3) given

dy/dx = (x + y)/x
y(2) = 1

Use h = 0.5 and h = 0.25
"""

import sys
import os
import matplotlib.pyplot as plt
import numpy as np
from colorama import Fore, Style


# Globals - Start Values
x = 2
y = 1
h1 = 0.25
h2 = 0.5


def eulers_(x: float, y: float, h: float) -> float:
    y = y + h * ((x + y) / x)
    x += h
    return x, y


def print_res(x: float, y: float, h: float, i: int) -> None:
    xval = []
    yval = []
    for _ in range(i):
        x, y = eulers_(x, y, h)
        xval.append(x)
        yval.append(y)
        print(f"{Fore.YELLOW}x{Fore.RESET}: {x:>7.3f} {' ':>5}", end="", flush=True)
        print(f"{Fore.CYAN}y{Fore.RESET}: {y:>7.3f}{' ':>5}")
        if x % 10 == 0:
            print(f"{Style.DIM}{'-':-^27}{Style.RESET_ALL}")
    return xval, yval


def plotter(
    xh1: list, xh2: list, y1: list, y2: list, i: int, h1: float, h2: float
) -> None:

    # Titles
    plt.figure("Niklas Lantau - Euler's Method")
    plt.suptitle(r"$y_{n}=y_{n-1}+hf(x_{n-1},y_{n-1})$")
    plt.title(r"Numerical: $\frac{dy}{dx}=\frac{x + y}{x}$")

    # Analytical values
    xval = np.arange(1, i, h2)
    yval = xval * np.log(np.abs(xval)) - 0.1931 * xval

    # Plot numerical
    plt.plot(xh1, y1, "r--", label=f"Numerical: h = {h1}")
    plt.plot(xh2, y2, "g:", label=f"Numerical: h = {h2}")
    plt.plot(
        xval,
        yval,
        "b-",
        label=r"Analytical: $x\ln\left | x \right | - 0.1931x$",
        alpha=0.4,
    )

    # Set graph limits and display legends
    plt.axis([0, 55, 0, 190])
    plt.legend()
    plt.grid(linewidth=0.5, which="major", linestyle="-")
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("> Need to provide the amount of x-values wanted")
        raise SystemExit
    else:
        try:
            iter_ = int(sys.argv[1])
            # Clear space above STDOUT
            print(*("\n" for _ in range(10)))

            print(f'{Fore.GREEN}{" START ":-^27}{Fore.RESET}')

            # ... and some below START - banner
            print(*("\n" for _ in range(10)))

            # Get h1 values
            print(f"{Fore.RED}{' h = 0.25 ':~^27}{Fore.RESET}")
            xh1, y1 = print_res(x, y, h1, iter_)

            # ... and some in between
            print(*("\n" for _ in range(10)))

            # Get h2 values
            print(f"{Fore.RED}{' h = 0.5 ':~^27}{Fore.RESET}")
            xh2, y2 = print_res(x, y, h2, iter_)

            # Plot 'em all!
            plotter(xh1, xh2, y1, y2, iter_, h1, h2)
        except ValueError:
            print(
                f"> {Fore.RED}ERROR{Fore.RESET}: 1rd arg needs to be an integer",
                file=sys.stderr,
            )
            raise SystemExit
