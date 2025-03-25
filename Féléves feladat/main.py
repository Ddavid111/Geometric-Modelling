import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
import math

def bezier_curve(control_points, t):
    n = len(control_points) - 1
    point = np.zeros(2)
    for i, p in enumerate(control_points):
        binomial_coeff = math.comb(n, i)
        point += binomial_coeff * (1 - t)**(n - i) * t**i * p
    return point

control_points = np.array([
    [1, 1], [3, 5], [7, 4], [8, 2], [6, 0], [3, 0], [1, 1]
])

t_vals = np.linspace(0, 1, 100)
curve_points = np.array([bezier_curve(control_points, t) for t in t_vals])

fig, ax = plt.subplots()

polygon = Polygon(curve_points, closed=True, facecolor='lightblue', alpha=0.4)
ax.add_patch(polygon)

ax.plot(curve_points[:, 0], curve_points[:, 1], color='blue', linewidth=2)

ax.set_xlim(-1, 10)
ax.set_ylim(-1, 6)

plt.show()
