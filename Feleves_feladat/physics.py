import numpy as np
from bezier import bezier_curve

def check_collision(position, control_points):
    """
    Ellenőrzi, hogy a mozgó pont közel van-e a Bézier-görbéhez.

    Args:
        position (np.ndarray): A pont aktuális pozíciója [x, y].
        control_points (np.ndarray): A Bézier-görbe kontrollpontjai.

    Returns:
        float or None: Az a t paraméterérték, ahol a legközelebbi pont van a görbén, vagy None ha nincs ütközés.
    """
    t_vals = np.linspace(0, 1, 1000)
    closest_t = None
    closest_dist = float('inf')
    for t in t_vals:
        curve_point = bezier_curve(control_points, t)
        dist = np.linalg.norm(position - curve_point)
        if dist < 0.1 and dist < closest_dist:
            closest_dist = dist
            closest_t = t
    return closest_t

def reflect_velocity(velocity, normal):
    """
    Visszaveri a mozgási sebességvektort az adott normál mentén.

    Args:
        velocity (np.ndarray): Az eredeti sebességvektor.
        normal (np.ndarray): A felület normálisa az ütközési pontban.

    Returns:
        np.ndarray: Az új, visszavert sebességvektor (csillapítva).
    """
    return (velocity - 2 * np.dot(velocity, normal) * normal) * 0.9

def calculate_normal(position, velocity, control_points):
    """
    Kiszámítja a Bézier-görbéhez tartozó normálvektort az adott pozíciónál, ha van ütközés.

    Args:
        position (np.ndarray): A mozgó pont pozíciója.
        velocity (np.ndarray): A pont aktuális sebességvektora.
        control_points (np.ndarray): A Bézier-görbe kontrollpontjai.

    Returns:
        np.ndarray: Az ütközési pontnál számított egységnyi normálvektor, vagy [0, 0] ha nincs ütközés.
    """
    t = check_collision(position, control_points)
    if t is None:
        return np.array([0, 0])
    curve_point = bezier_curve(control_points, t)
    next_point = bezier_curve(control_points, min(t + 0.01, 1.0))
    tangent = next_point - curve_point
    normal = np.array([-tangent[1], tangent[0]])
    return normal / np.linalg.norm(normal)
