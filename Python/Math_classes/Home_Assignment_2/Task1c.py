# -*- coding: utf-8 -*-
# nlantau, 2020-05-11
# Task 1c, Home Assignment 2, MA111A

import matplotlib.pyplot as plt
import numpy as np

def yx(x,opacity):
    y = ((x**3)/3) - ((5*x**2)/2) + (4*x) + 3
    plot(x, y, 'b-', r'$y(x)$',opacity)
     
def yx_extreme_points(xlim, color, label, text, x_y, xy_text):
    ylim = ((xlim**3)/3) - ((5*xlim**2)/2) + (4*xlim) + 3
    plot(xlim,ylim,color,label,1)
    plt.annotate(text,
            xy=(x_y), xycoords='data',
            xytext=(xy_text), textcoords='data',
            arrowprops=dict(arrowstyle="-|>",
                            connectionstyle="arc3"),
            ) 

def setup_env(list1, list2):
    #plt.figure(dpi=150)
    plt.axhline(0, color='black')
    plt.axvline(0, color='black')
    plt.axis([-3, 8, -4, 15])
    plt.xticks([x for x in list1], rotation=0)
    plt.yticks([x for x in list2], rotation=0)
    plt.grid(b=True, which='major')
    plt.xlabel('x')
    plt.ylabel('y')

def legends(supt, tit):
    plt.legend()
    plt.suptitle(supt)
    plt.title(tit)
    plt.show()
    
def plot_points(xlim):
    return ((xlim**3)/3) - ((5*xlim**2)/2) + (4*xlim) + 3
    
def plot(x, y, style, label, opacity):
    plt.plot(x, y, style, label=label, alpha=opacity)
    
def main():
    setup_env(np.arange(-3,8,1), np.arange(-4,15,1))
    yx(np.arange(-2.0, 15, 0.1),1)
    plot_points(np.arange(1, 5.1, 1))
    yx_extreme_points(np.arange(4, 6, 2.), 'go', 'Min', r"$Min (4,\frac{1}{3})$", (4, (1/3)), (3.4, 5))
    yx_extreme_points(np.arange(1, 3, 2.), 'ro', 'Max', r"$Max (1,\frac{29}{6})$", (1, (29/6)), (0.3, 1))
    legends('Home Assignment 2, Task 1 c)', r"$y(x) = \frac{x^{3}}{3}-\frac{5x^{2}}{2}+4x+3$")

if __name__ == "__main__":
    main()