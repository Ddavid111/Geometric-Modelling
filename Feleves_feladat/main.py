# Standard library
import json

# Third-party library
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.animation import FuncAnimation

# Saját modulok
from bezier import bezier_curve
from animation import BouncingPoint


def main():
    """
    Elindítja a Bézier-görbén pattogó pont animációját.
    A kontrollpontokat JSON fájlból olvassa be.
    """

    with open("Feleves_feladat/control_points.json", "r") as f:
        data = json.load(f)

    print("Elérhető kontrollpont készletek:")
    for key in data:
        print(f" - {key}")
    choice = input("Melyik kontrollpont készletet szeretnéd használni? (pl. set1): ").strip()
    if choice not in data:
        print(f"Ismeretlen készlet: {choice}, az alapértelmezett 'set1' lesz használva.")
        choice = "set1"

    control_points = np.array(data[choice])

    curve_points = np.array([bezier_curve(control_points, t) for t in np.linspace(0, 1, 1000)])
    points = [
    BouncingPoint([4.0, 3.0], [1.0, -0.8], control_points),
    BouncingPoint([5.0, 2.0], [-0.3, 0.5], control_points),
    BouncingPoint([3.0, 2.0], [0.2, 0.6], control_points)
    ]

    fig, ax = plt.subplots()
    fig.canvas.manager.set_window_title("Bézier-Görbe Animáció")

    polygon = Polygon(curve_points, closed=True, facecolor='lightblue', alpha=0.4)
    ax.add_patch(polygon)
    ax.plot(curve_points[:, 0], curve_points[:, 1], color='blue', linewidth=2, label="Zárt Bézier-görbe")

    scats = [ax.scatter(*p.position, s=100, label=f"Pattogó pont {i+1}") for i, p in enumerate(points)]
    ax.set_xlim(-1, 10)
    ax.set_ylim(-3, 7)
    ax.legend()

    def animate(frame):
        for point, scat in zip(points, scats):
            pos = point.update() 
            scat.set_offsets(pos)
        return scats

    ani = FuncAnimation(fig, animate, frames=100, interval=1, blit=True)
    plt.show()


if __name__ == "__main__":
    main()
