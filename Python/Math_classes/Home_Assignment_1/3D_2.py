import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x = np.zeros(10)
x = [0,0,0,2,2,2]
y = np.zeros(10)
z = np.arange(10)
dx = np.zeros(10)
dy = np.arange(10)
dz = np.zeros(10)

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.quiver(x, y, z, dx, dy, dz)
ax.set_ylim(0,10)

plt.show()