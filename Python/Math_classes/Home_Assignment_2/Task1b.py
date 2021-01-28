# -*- coding: utf-8 -*-
# nlantau, 2020-05-14
# Task 1b, Home Assignment 2, MA111A

#import matplotlib.pyplot as plt
import numpy as np
from Task1c import setup_env,legends,plot,yx

def local_extreme_point(x, color, label, opacity):
    y = ((x**3)/3) - ((5*x**2)/2) + (4*x) + 3
    plot(x,y,color,label,opacity)

def main():
    setup_env(np.arange(-3, 8, 1), np.arange(-4, 15, 1))
    yx(np.arange(-2.0, 15, 0.1),0.2)
    local_extreme_point(np.arange(0.2, 0.9, 0.1),'g--',"Indicating Max", 1)
    local_extreme_point(np.arange(1.2, 1.9, 0.1),'g--',r"$y''(x) < 0$", 1)
    
    local_extreme_point(np.arange(3.2, 3.9, 0.1),'r--','Indicating Min', 1)  
    local_extreme_point(np.arange(4.2, 4.9, 0.1),'r--',r"$y''(x) > 0$", 1) 
    legends('Home Assignment 2, Task 1 b)', r"$y(x) = \frac{x^{3}}{3}-\frac{5x^{2}}{2}+4x+3$")
    
if __name__ == "__main__":
    main()