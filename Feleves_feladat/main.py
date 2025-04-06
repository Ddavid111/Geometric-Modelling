import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.animation import FuncAnimation
from bezier import bezier_curve
from animation import BouncingPoint


def main():
    """
    Elindítja a Bézier-görbén pattogó pont animációját.

    Beállítja a görbét, a mozgó pontot és elindítja a matplotlib animációt.
    """
    control_points = np.array([
        [1, 1], [3, 5], [7, 4], [8, 2], [6, 0], [3, 0], [1, 1]
    ])
    curve_points = np.array([bezier_curve(control_points, t) for t in np.linspace(0, 1, 1000)])
    point = BouncingPoint([4.0, 3.0], [0.5, -0.4], control_points)

    fig, ax = plt.subplots()
    fig.canvas.manager.set_window_title("Bézier-Görbe Animáció")

    polygon = Polygon(curve_points, closed=True, facecolor='lightblue', alpha=0.4)
    ax.add_patch(polygon)
    ax.plot(curve_points[:, 0], curve_points[:, 1], color='blue', linewidth=2, label="Zárt Bézier-görbe")

    scat = ax.scatter(*point.position, color='red', s=100, label="Pattogó pont")
    ax.set_xlim(-1, 10)
    ax.set_ylim(-1, 6)
    ax.legend()

    def animate(frame):
        pos = point.update()
        scat.set_offsets(pos)
        return scat,

    ani = FuncAnimation(fig, animate, frames=600, interval=16, blit=True)
    plt.show()

if __name__ == "__main__":
    main()
