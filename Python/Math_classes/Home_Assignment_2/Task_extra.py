# -*- coding: utf-8 -*-
# nlantau, 2020-05-11
# Task Extra Functions, Home Assignment 2, MA111A

import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np
from Task1c import legends, setup_env, plot, yx
  

def print_area_and_x_value(l1, l2):
    counter, area, real_area= 0,0,0
    l_area = []                                 # List containing area
    l_x_val = []                                # List containing x-values
    l_y_val = []                                # List containing y-values
    print(f'{" Result ":~^30}')
    print(f'Area\tX Range\t\tX Value\t\tY Value')
    for (a,b) in zip(l1, l2):
        counter += 1
        area += b
        real_area += b
        if(counter % 1 == 0):
            print(f'{area:.3f} \t{a-0.9:.1f}-{a+0.1:.1f}\t\t{a+0.1:.1f}\t\t{(area)/(a+0.1):.2f}')
            l_area.append(area)
            l_x_val.append(a+0.1)
            l_y_val.append((area)/(a+0.1))
            area = 0
    print(f'Approximated Area: {real_area:.4f}')
    return l_area, l_x_val, l_y_val

def callers():
   
#l_a, l_x, l_y = print_area_and_x_value(np.arange(1, 5, 1), area_rec(np.arange(1, 5, 1), 1))
#print(f'Area:\n{l_a}')
#print(f'X Value:\n{l_x}')
#print(f'Y value:\n{l_y}')


if __name__ == "__main__":
    print(f'{"Dont use me as source":~^50}')