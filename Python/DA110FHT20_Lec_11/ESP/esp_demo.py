import matplotlib.pyplot as plt


def get_data(file):
    return [float(i.split("\t")[1].strip("\n")) for i in open(r"" + file, "r")]


def plot(pos, data, opt, label):
    plt.subplot(pos)
    plt.axis([400, 800, -1, 6])
    plt.plot(data, opt, label=label)
    plt.xlabel("2 cycles (0.016 s/cycle)")
    plt.ylabel("Voltage")
    plt.grid(True)
    plt.legend()


def main():

    # Collect values from textfile
    x5_0v = get_data("xy_5V.txt")
    x2_5v = get_data("xy_2,5v.txt")
    x0_5v = get_data("xy_0,5v.txt")

    # Plot
    plot(131, x5_0v, "r-", "4.95V")
    plot(132, x2_5v, "g-", "2.5V")
    plot(133, x0_5v, "k-", "0.5V")

    # Project title
    plt.suptitle("PWM Example DA110F HT20")

    # Display graph
    plt.show()


if __name__ == "__main__":
    main()
