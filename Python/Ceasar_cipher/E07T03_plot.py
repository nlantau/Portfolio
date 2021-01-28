# nlantau, 2020-07-12
""" Plot module for E07T03.py """

import matplotlib.pyplot as plt
import numpy as np
from E07T03 import analyze_freq
from timer import timer


@timer
def create_x_y_values(alpha_dic: dict) -> list:
    """ Put keys and values in separate lists
    return x: list and y: list
    """

    x = [x for x in alpha_dic]
    yvals = [alpha_dic[values] for values in alpha_dic]
    tot = sum(yvals)
    y = [(alpha_dic[values] / tot) * 100 for values in alpha_dic]
    return x, y, tot


def create_dict_eng_values():
    """ Values taken from wikipedia
    https://en.wikipedia.org/wiki/Letter_frequency
    """

    letters = [chr(97 + k) for k in range(26)]
    with open("eng_val.txt", "r") as reader:
        values = reader.read().split(",")
    val = [float(x) for x in values]

    return {k: v for (k, v) in zip(letters, val)}


def plot_bar(x, y, tot_vals, x2, y2, tot_vals2, filename):
    """ Plot x: list against y: list using matplotlib """

    # Figure title, dpi
    plt.figure("E07T03 Frequency Plot", dpi=150)

    # Init subplot 211
    plt.subplot(211)

    # Plot subplot 211
    plt.title(
        f"Frequency Analyzis of English Language\n{tot_vals2:.0f} values (wikipedia)"
    )
    plt.ylabel("Occurence in percentage (%)")
    plt.xlabel("Letter")
    plt.yticks([x for x in np.arange(0, 20, 2)])
    plt.ylim(top=14)

    plt.grid(color="grey", linewidth=0.2)
    plt.bar(x2, y2)

    # Init subplot 212
    plt.subplot(212)

    # Plot subplot 212
    plt.title(f"Frequency Analyzis of {filename!r}\n{tot_vals} letters analayzed")
    plt.ylabel("Occurence in percentage (%)")
    plt.xlabel("Letter")
    plt.yticks([x for x in np.arange(0, 20, 2)])
    plt.ylim(top=14)

    plt.grid(color="grey", linewidth=0.2)
    plt.bar(x, y)

    # Adjust space between plots
    plt.subplots_adjust(hspace=1)

    # Display plot
    plt.show()


if __name__ == "__main__":
    import sys

    if len(sys.argv) < 2:
        # File to be plotted
        filename = "shift_neg_3_encrypted.txt"
    elif sys.argv[1]:
        filename = sys.argv[1]

    # Get an analyzed dictionary by helper module
    analyzed_dict = analyze_freq(filename)

    # Letter frequency in english
    eng_dict = create_dict_eng_values()

    # Create plotting values for text file and eng lang
    x, y, tot_vals = create_x_y_values(analyzed_dict)
    x2, y2, tot_vals2 = create_x_y_values(eng_dict)

    # Plot it!
    plot_bar(x, y, tot_vals, x2, y2, tot_vals2, filename)
