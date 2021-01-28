# -*- coding: utf-8 -*-
# nlantau, 2020-05-11
# Task 2a, Home Assignment 2, MA111A

import matplotlib.pyplot as plt
import numpy as np
from Task1c import legends, setup_env, plot

def yx(x):
    return ((x**3)/3) - ((5*x**2)/2) + (4*x) + 3

def plot_auc(lim):
    filler(lim, yx(lim), 0, 'red')

def filler(x, y, val, color):
    plt.fill_between(x, y, val, color=color, label=r"$\int_{1}^{5}y(x)dx$")
    
def main():
    setup_env(np.arange(-3,8,1), np.arange(-4,15,1))
    plot_auc(np.arange(1, 5, 0.01))
    plot(np.arange(-2.0, 15, 0.1), yx(np.arange(-2.0, 15, 0.1)), 'b-', r'$y(x)$', 1)

    plt.text(0.1, 6, r"$Area: \int_{1}^{5}(\frac{x^{3}}{3}-\frac{5x^{2}}{2}+4x+3)dx = \frac{26}{3} a.u. $", bbox={'facecolor':'red','alpha':0.4,'pad':3})
    legends('Home Assignment 2, Task 2 a)',r"$y(x) = \frac{x^{3}}{3}-\frac{5x^{2}}{2}+4x+3$" )
  
    
if __name__ == "__main__":
    main()