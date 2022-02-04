# nlantau, 2020-11-12
"""
Plott module for algorithm run time results
"""
import sys
import os
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from colorama import Fore, Back, Style


root = r"/Users/nlantau/docs/GitHub/DT256CHT20/Results/"
algo = "Merge Sort - Iterative"
# tit = "From 100 to 1,000,000 sized arrays"
tit = "1K to 10M"


def pd_read(path):
    return pd.read_csv(path)


def main(path):
    plt.figure("Niklas Lantau - DT256C Seminar 1")
    plt.suptitle(algo)

    # Get x- and y-values from CSV file
    y = pd_read(path)["Seconds"]
    x = pd_read(path)["Size"]

    # Sort the obtained values
    x2 = x.sort_values()
    y3 = y.sort_values()

    # Scatter plot - This is our actual data being plotted
    plt.scatter(x, y, marker="_")

    # Polyfit - Trendline
    # z = np.polyfit(np.log(x2), y3, 1)
    z = np.polyfit(x2, y3, 2)
    p = np.poly1d(z)

    plt.plot(x2, p(x2), "r-")
    print(f'y = {z[0]:}x + {z[1]}')

    # ...
    plt.title(tit)
    plt.grid()
    plt.ylabel("Seconds")
    plt.xlabel("Size")
    axs = plt.gca()
    axs.get_xaxis().get_major_formatter().set_scientific(False)

    plt.show()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("> Need to provide path to text file containing numbers as sys argv")
        print("> Example: python plotter.py IS_iter2.CSV")
        raise SystemExit
    elif os.path.exists(path := os.path.abspath(root + sys.argv[1])):
        main(path)
    else:
        print(f"\n> {Fore.RED}ERROR{Fore.RESET} File does not exist...")
        print("> Stopping program\n")
        raise SystemExit
