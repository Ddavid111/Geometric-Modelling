# Third-party library
import numpy as np

# Saját modulok
from bezier import bezier_curve, bezier_derivative

SAMPLE_RESOLUTION = 1000  # Globális konstans a mintavételezéshez
COLLISION_THRESHOLD = 0.1  # Ütközési küszöb

def find_curve_collision(start_pos, end_pos, control_points, samples=SAMPLE_RESOLUTION):
    """
    Megkeresi, hogy a pont útvonala metszi-e a Bézier-görbét.

    Args:
        start_pos (np.ndarray): Kiinduló pozíció.
        end_pos (np.ndarray): Cél pozíció.
        control_points (np.ndarray): A Bézier-görbe kontrollpontjai.
        samples (int): Mintavételezési felbontás.

    Returns:
        float or None: Az ütközéshez legközelebbi t érték, vagy None ha nincs ütközés.
    """
    t_vals = np.linspace(0, 1, samples)
    min_dist = float('inf')
    best_t = None
    motion_vec = end_pos - start_pos
    seg_length = np.linalg.norm(motion_vec)

    if seg_length == 0:
        return None

    for t in t_vals:
        curve_point = bezier_curve(control_points, t)
        to_curve = curve_point - start_pos
        proj = np.dot(to_curve, motion_vec) / seg_length
        if 0 <= proj <= seg_length:
            dist = np.linalg.norm(np.cross(motion_vec, to_curve) / seg_length)
            if dist < COLLISION_THRESHOLD and dist < min_dist:
                min_dist = dist
                best_t = t
    return best_t

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

def calculate_normal(t, control_points):
    """
    Kiszámítja a normálvektort a görbén a t paraméterhez tartozó pontnál.

    Args:
        t (float): Paraméterérték az ütközési pontnál.
        control_points (np.ndarray): A Bézier-görbe kontrollpontjai.

    Returns:
        np.ndarray or None: Egységnyi normálvektor, vagy None ha nem számítható.
    """
    derivative = bezier_derivative(control_points, t)
    if np.linalg.norm(derivative) == 0:
        return None
    tangent = derivative / np.linalg.norm(derivative)
    normal = np.array([-tangent[1], tangent[0]])
    return normal / np.linalg.norm(normal)
