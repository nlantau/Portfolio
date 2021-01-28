#!/usr/bin/python3
# nlantau, 2020-04-21

info=('''
    4x + y + 3z = 15
    2x - y + 4z = 12
         y + 5z = 17

Find the 3x3 matrix inverse

''')
import numpy as np

m_list = [[4,1,3],[2,-1,4],[0,1,5]]
m_equ = [15,12,17]

A = np.array(m_list)
B = np.array(m_equ)

xyz_solved = np.linalg.inv(A).dot(B)        # Solve for x,y,z
inv_A = np.linalg.inv(A)                    # Inverse 3x3 matrix
X = inv_A.dot(A)
np.set_printoptions(suppress=True)          # Suppress small results

print('{:*^30}'.format(' Task 2: Information '))
print(info)
print('{:*^30}'.format(' Task 2: Solutions '))
print("Values for x, y, z:\n ",xyz_solved)
print("Inverse:\n", inv_A)
print("\n")
print('{:*^30}'.format(' Task 2: Inv_A x A = I '))

print("Inverse x A: \n", X)
