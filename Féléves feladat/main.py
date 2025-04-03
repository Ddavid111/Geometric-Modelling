import numpy as np
import matplotlib.pyplot as plt
import math
from matplotlib.animation import FuncAnimation
from matplotlib.patches import Polygon

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

t_vals = np.linspace(0, 1, 1000)
curve_points = np.array([bezier_curve(control_points, t) for t in t_vals])

position = np.array([4.0, 3.0])
velocity = np.array([0.5, -0.4])

def check_collision(position, velocity, control_points):
    t_vals = np.linspace(0, 1, 1000)
    closest_t = None
    closest_dist = float('inf')
    for t in t_vals:
        curve_point = bezier_curve(control_points, t)
        dist = np.linalg.norm(position - curve_point)
        if dist < 0.1:
            if dist < closest_dist:
                closest_dist = dist
                closest_t = t
    return closest_t

def reflect_velocity(velocity, normal):
    reflected_velocity = velocity - 2 * np.dot(velocity, normal) * normal
    return reflected_velocity * 0.9

def calculate_normal(position, control_points):
    t = check_collision(position, velocity, control_points)
    if t is None:
        return np.array([0, 0])
    curve_point = bezier_curve(control_points, t)
    next_curve_point = bezier_curve(control_points, t + 0.01)
    tangent = next_curve_point - curve_point
    normal = np.array([-tangent[1], tangent[0]])
    normal = normal / np.linalg.norm(normal)
    return normal

def update(frame):
    global position, velocity
    t_collision = check_collision(position, velocity, control_points)
    
    if t_collision is not None:
        normal = calculate_normal(position, control_points)
        velocity = reflect_velocity(velocity, normal)
    
    position += velocity * 0.05
    
    scat.set_offsets(position)
    return scat,

fig, ax = plt.subplots()

fig.canvas.manager.set_window_title("Bézier-Görbe Animáció")

polygon = Polygon(curve_points, closed=True, facecolor='lightblue', alpha=0.4)
ax.add_patch(polygon)

ax.plot(curve_points[:, 0], curve_points[:, 1], color='blue', linewidth=2, label="Zárt Bézier-görbe")

scat = ax.scatter(position[0], position[1], color='red', s=100, label="Pattogó pont")

ax.set_xlim(-1, 10)
ax.set_ylim(-1, 6)
ax.legend()

ani = FuncAnimation(fig, update, frames=600, interval=16, blit=True)

plt.show()
