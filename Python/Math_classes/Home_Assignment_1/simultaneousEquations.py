#!/usr/bin/python3
# nlantau, 2020-04-17
''' System of Equations
    Jacobi's method
    4x + y + 3z = 15
    2x – y + 4z = 12
    y + 5z = 17
'''
# Start values
print("--------------------------------------------")
print("Home Assignment 1\nAlgebra and Calculus\n")
print("4x + y + 3z = 15\n2x – y + 4z = 12\ny + 5z = 17\n\n")

x1 = float(input("Enter start x value: ")) # 1.5
y1 = float(input("Enter start y value: ")) # 2.5
z1 = float(input("Enter start z value: ")) # 3
print("--------------------------------------------")

# Functions for finding x,y,z
def find_x(y,z):
    return -(3.0/4.0)*z - (y/4.0) + (15.0/4.0)

def find_y(x,z):
    return -12.0 + 2.0*x + 4.0*z

def find_z(y):
    return (17.0/5.0) - (y/5.0)

# Function for finding next x,y,z
def test_first(x,y,z):
    x2 = find_x(y,z)
    y2 = find_y(x,z)
    z2 = find_z(y)
    return x2, y2, z2

# Let user enter amount
iterations = int(input("Enter amount of iterations: "))
print("\t x    \t\t\t y    \t\t\t z    ")
# print as many iterations as you'd like 
for i in range(iterations):
    x1, y1, z1 = test_first(x1, y1, z1)
    print(i+1,'\t',format(x1, '.4f'),'\t\t', format(y1,'.4f'),'\t\t', format(z1,'.4f')) 


print("\nSolved with Jacobi's Method\n\n")

