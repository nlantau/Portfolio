#!/usr/bin/python3
# nlantau, 2020-04-21
# updated 2020-05-07
# Home Assignement 1, MA111A

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

r_old = [2, 3, 4, 5, 17, 1]               # [2, 2, 2] given to group 9
r_new = [2, 3, 4, -9, -5, -1]
unitvector0 = []
unitvector1 = [7, -17, 1, -5,  20,  4]
unitvector2 = [2,   3, 5,  5, -20, -4]

# list of lists
soa = np.array([
     r_old,                 # uncomment to display r_old
     r_new,                 # uncomment to display r_new
     #trans,                  # uncomment to display trans
    #unitvector0,               # uncomment to display v_newnew
    #unitvector2
])

# create coordinate tuple of lists [(X,x1),(Y,y1),(Z,z1),(U,x2),(V,y2),(W,z2)]
# if only v_newnew is in soa:
# above is false; X = (0,), Y = (0,), Z = (0,), U = (3,), V = (-6.3301, ), W = (0.941, )

X, Y, Z, U, V, W = zip(*soa)

# set 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d', label='test')


# set arrows
ax.quiver(X, Y, Z, U, V, W, color='black',
          arrow_length_ratio=0.05, lw=1, label='Bög-vektor')

plt.xlabel('x')
# plt.zlabel('z')
plt.ylabel('y')
plt.title('(5,-20,-4) och (-5,20,4)')

ax.text(2,   3.3, 5.2, "[5, -20, -4]", color='red')
ax.text(7, -17.3, 1.2, "[-5, 20, 4]", color='red')
# set axis limits
ax.set_xlim([0, 8])
ax.set_ylim([2, 17])
ax.set_zlim([0, 6])
plt.xticks([x for x in np.arange( -5, 7, 1)], rotation=45)
plt.yticks([x for x in np.arange(-20, 3, 3)], rotation=45)

plt.legend()

# display 3D graph
plt.show()
