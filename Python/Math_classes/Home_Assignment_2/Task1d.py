# -*- coding: utf-8 -*-
# nlantau, 2020-05-11
# Task 1d, Home Assignment 2, MA111A

import matplotlib.pyplot as plt
import numpy as np
from Task1c import setup_env,legends

def yx(x):
    return ((x**3)/3) - ((5*x**2)/2) + (4*x) + 3

def dyx(x):
    return (x**2) - 5*x + 4
    
def numerical_dy_approx(x,n):
    return ( yx(x+n)-yx(x) ) / ((x+n)-(x))
        
def print_yx(x):   
    plt.plot(x, dyx(x), label=r"$y'(x)$")
    
def print_approx_dy(list1,n,label):
    plt.plot(list1, [numerical_dy_approx(x,n) for x in list1], label=label)       
    
def main():
    plt.subplot(121)
    setup_env(np.arange(-3, 8, 1), np.arange(-4, 15, 1))
    
    print_approx_dy(np.arange(-2, 15, 0.1), 0.1, r'$\frac{y[n+0.1]-y[n]}{\Delta x}$')
    
    print_yx(np.arange(-2.0, 15, 0.1) )
    legends('Home Assignment 2, Task 1 d)','Approximation 0.1' )



    plt.subplot(122)
    setup_env(np.arange(-3, 8, 1), np.arange(-4, 15, 1))
    plt.axis([-3, 8, -4, 15])
    
    print_approx_dy(np.arange(-2, 15, 0.1), 1, r'$\frac{y[n+1]-y[n]}{\Delta x}$')
    
    print_yx(np.arange(-2.0, 15, 0.1) )
    legends('Home Assignment 2, Task 1 d)','Approximation 1.0' )
    
if __name__ == "__main__":
    main()