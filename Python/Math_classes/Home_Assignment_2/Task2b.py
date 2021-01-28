# -*- coding: utf-8 -*-
# nlantau, 2020-05-11
# Task 2b, Home Assignment 2, MA111A

import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np
from Task1c import legends, setup_env, plot

def yx(x):
    return ((x**3)/3) - ((5*x**2)/2) + (4*x) + 3

def filler(x, y, val, color):
    plt.fill_between(x, y, val, color=color, label=r"$\int_{1}^{5}y(x)dx$")  

def draw_rectangle():
    ax = plt.gca()
    rect1 = Rectangle((1,yx(1.5)),1,-yx(1.5),linewidth=1.1, edgecolor='r',facecolor='r')
    rect2 = Rectangle((2,yx(2.5)),1,-yx(2.5),linewidth=1.1, edgecolor='g',facecolor='g')
    rect3 = Rectangle((3,yx(3.5)),1,-yx(3.5),linewidth=1.1, edgecolor='r',facecolor='r')
    rect4 = Rectangle((4,yx(4.5)),1,-yx(4.5),linewidth=1.1, edgecolor='g',facecolor='g')
    ax.add_patch(rect1)
    ax.add_patch(rect2)
    ax.add_patch(rect3)
    ax.add_patch(rect4)    

def main():
    setup_env(np.arange(-3,8,1), np.arange(-4,15,1))
    plot(np.arange(-2.0, 15, 0.1), yx(np.arange(-2.0, 15, 0.1)), 'b-', r'$y(x)$', 1)
    draw_rectangle()
    plt.text(0.1, 6, r"$A[n] = y[n] \Delta x = 8.5 a.u. $", bbox={'facecolor':'red','alpha':0.4,'pad':3})
    legends('Home Assignment 2, Task 2 b)',r"$y(x) = \frac{x^{3}}{3}-\frac{5x^{2}}{2}+4x+3$" )  
    
if __name__ == "__main__":
    main()