# -*- coding: utf-8 -*-
# nlantau, 2020-05-11
# Task 2c, Home Assignment 2, MA111A

import matplotlib.pyplot as plt
import numpy as np
from Task1c import legends, setup_env, plot  

def yx(x):
    return ((x**3)/3) - ((5*x**2)/2) + (4*x) + 3
 
def area_trapezium(h,x,n):
    return (h/2) * ( yx(x) + yx(x+n) )

def annotate_(text, x_y, xy_text, width):
    plt.annotate(text,
        xy=(x_y), xycoords='data',
        xytext=(xy_text), textcoords='data',
        arrowprops={'arrowstyle': width }
        ) 

def print_text():
    annotate_('', ( 1.0, 2.45), (0.7, 2.45), '-[, widthB=3.4,lengthB=0.2')
    annotate_('', ( 2.0, 1.90), (1.7, 1.90), '-[, widthB=2.6,lengthB=0.2')
    annotate_('', ( 0.9, -1.0), (2.1, -1.0), '<|-|>, head_length=0.3,head_width=0.2')
    plt.text(0.4, 2.20, r'${y_{i}}$')
    plt.text(1.1, 2.20, r'${y_{i+1}}$')
    plt.text(1.4, -1.9,r'h')
    plt.text(0.1, 8.00, r"$\frac{h}{2}[{y_{i}}+{y_{i+1}}]\:\{i: i\in \mathbb{N} \:and\: 1\leqslant \: i< 5\}$", bbox={'facecolor':'red','alpha':0.4,'pad':3})
    legends('Home Assignment 2, Task 2 c)',r"$y(x) = \frac{x^{3}}{3}-\frac{5x^{2}}{2}+4x+3$" )
            
def calc_area(a,b,c):
    print(f'{" Task 2c ":~^40}')
    print(f'X Value\t\tT.Area\t\tSec.Area'); i=0
    for x in range(a, b, c):
        i += area_trapezium(a, x, c)
        print(f'{x}\t\t{i:.3f}\t\t{area_trapezium(a, x, c):.3f}')
    
def main():
    setup_env(np.arange(-3,8,1), np.arange(-4,15,1))
    plot(np.arange(-2.0, 15, 0.1), yx(np.arange(-2.0, 15, 0.1)), 'b-', r'$y(x)$', 0.2)
    plt.stem(np.arange(1,5.1,1), yx(np.arange(1,5.1,1)),'r',markerfmt='r-',label='Trapezoidal', use_line_collection=True)
    print_text()    
    calc_area(1, 5, 1)      

if __name__ == "__main__":
    main()