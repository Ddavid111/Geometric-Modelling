import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.animation import FuncAnimation
from bezier import bezier_curve
from animation import BouncingPoint
import json


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
    point = BouncingPoint([4.0, 3.0], [0.5, -0.4], control_points)

    fig, ax = plt.subplots()
    fig.canvas.manager.set_window_title("Bézier-Görbe Animáció")

    polygon = Polygon(curve_points, closed=True, facecolor='lightblue', alpha=0.4)
    ax.add_patch(polygon)
    ax.plot(curve_points[:, 0], curve_points[:, 1], color='blue', linewidth=2, label="Zárt Bézier-görbe")

    scat = ax.scatter(*point.position, color='red', s=100, label="Pattogó pont")
    ax.set_xlim(-1, 10)
    ax.set_ylim(-3, 7)
    ax.legend()

    def animate(frame):
        pos = point.update()
        scat.set_offsets(pos)
        return scat,

    ani = FuncAnimation(fig, animate, frames=600, interval=16, blit=True)
    plt.show()


if __name__ == "__main__":
    main()
