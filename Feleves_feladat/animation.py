# Third-party library
import numpy as np

# Saját modulok
from physics import find_curve_collision, reflect_velocity, calculate_normal

class BouncingPoint:
    """
    Egy mozgó pontot modellez, amely egy Bézier-görbéhez ütközve visszapattan.

    Attribútumok:
        position (np.ndarray): A pont aktuális pozíciója.
        velocity (np.ndarray): A pont sebességvektora.
        control_points (np.ndarray): A Bézier-görbe kontrollpontjai.
    """

    def __init__(self, position, velocity, control_points):
        self.position = np.array(position, dtype=float)
        self.velocity = np.array(velocity, dtype=float)
        self.control_points = control_points

    def update(self, dt=0.05):
        next_position = self.position + self.velocity * dt
        t_collision = find_curve_collision(self.position, next_position, self.control_points)

        if t_collision is not None:
            normal = calculate_normal(t_collision, self.control_points)
            if normal is not None:
                self.velocity = reflect_velocity(self.velocity, normal)

        self.position += self.velocity * dt
        return self.position
