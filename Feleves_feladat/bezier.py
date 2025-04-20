# Standard library
import math

# Third-party library
import numpy as np


def bezier_curve(control_points, t):
    """
    Bézier-görbe pont számítása de Casteljau algoritmussal.
    """
    n = len(control_points) - 1
    points = np.array(control_points)

    for r in range(1, n + 1):
        points = points[:-1] * (1 - t) + points[1:] * t

    return points[0]


def bezier_derivative(control_points, t):
    """
    Bézier-görbe első deriváltját számolja ki.

    Args:
        control_points (np.ndarray): Kontrollpontok (Nx2).
        t (float): Paraméter [0, 1].

    Returns:
        np.ndarray: Az érintő vektor a görbén.
    """
    n = len(control_points) - 1
    diff = np.array([
        n * (control_points[i + 1] - control_points[i])
        for i in range(n)
    ])
    return bezier_curve(diff, t)


def bezier_curve(control_points, t):
    """
    Bézier-görbe pont számítása de Casteljau algoritmussal.
    """
    n = len(control_points) - 1
    points = np.array(control_points)

    for r in range(1, n + 1):
        points = points[:-1] * (1 - t) + points[1:] * t

    return points[0]

def bezier_derivative(control_points, t):
    """
    Bézier-görbe első deriváltját számolja ki.

    Args:
        control_points (np.ndarray): Kontrollpontok (Nx2).
        t (float): Paraméter [0, 1].

    Returns:
        np.ndarray: Az érintő vektor a görbén.
    """
    n = len(control_points) - 1
    diff = np.array([
        n * (control_points[i + 1] - control_points[i])
        for i in range(n)
    ])
    return bezier_curve(diff, t)
