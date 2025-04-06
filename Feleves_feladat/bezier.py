import numpy as np

def bezier_curve(control_points, t):
    """
    Egy Bézier-görbe adott pontját számítja ki a t paraméter értéke alapján.

    Args:
        control_points (np.ndarray): A Bézier-görbe kontrollpontjai (Nx2-es tömb).
        t (float): Paraméter [0, 1] tartományban, amely a görbe menti pozíciót jelöli.

    Returns:
        np.ndarray: A görbe megfelelő pontjának [x, y] koordinátái.
    """
    n = len(control_points) - 1
    points = np.array(control_points)

    for r in range(1, n + 1):
        points = points[:-1] * (1 - t) + points[1:] * t

    return points[0]
