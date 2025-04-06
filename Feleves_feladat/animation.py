import numpy as np
from physics import check_collision, reflect_velocity, calculate_normal

class BouncingPoint:
    """
    Egy mozgó pontot modellez, amely egy Bézier-görbéhez ütközve visszapattan.

    Attribútumok:
        position (np.ndarray): A pont aktuális pozíciója.
        velocity (np.ndarray): A pont sebességvektora.
        control_points (np.ndarray): A Bézier-görbe kontrollpontjai.
    """

    def __init__(self, position, velocity, control_points):
        """
        Létrehoz egy új mozgó pont objektumot.

        Args:
            position (list or np.ndarray): A kezdeti pozíció [x, y].
            velocity (list or np.ndarray): A kezdeti sebesség [vx, vy].
            control_points (np.ndarray): A Bézier-görbe kontrollpontjai.
        """
        self.position = np.array(position, dtype=float)
        self.velocity = np.array(velocity, dtype=float)
        self.control_points = control_points

    def update(self, dt=0.05):
        """
        Frissíti a pont pozícióját egy időlépés alapján.

        Ha a pont közel kerül a Bézier-görbéhez, akkor ütközést detektál és visszapattan.

        Args:
            dt (float): Az időlépés nagysága (alapértelmezett: 0.05).

        Returns:
            np.ndarray: Az új pozíció.
        """
        t_collision = check_collision(self.position, self.control_points)
        if t_collision is not None:
            normal = calculate_normal(self.position, self.velocity, self.control_points)
            self.velocity = reflect_velocity(self.velocity, normal)
        self.position += self.velocity * dt
        return self.position
