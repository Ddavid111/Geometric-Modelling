# Geometric-Modelling

**Név:** Drig Dávid  
**Neptun kód:** EZ3YRC

# Féléves Feladat: Zárt Bézier-Görbén Belüli Pattogó Pont

## Feladat Leírása

Implementáljunk egy alkalmazást, amely egy zárt Bézier görbén belül pattogó pontot jelenít meg! Az alkalmazás célja, hogy szimulálja egy pont mozgását a Bézier-görbe által határolt területen, valamint megjelenítse a görbét és annak kitöltött területét. A pont a Bézier-görbével való érintkezéskor tükröződik, szimulálva a fizikai ütközést.

## Számítási Módszerek és Ütközéskezelés

A pont mozgása és a Bézier-görbével való ütközések kezelése során a következő számításokat végezzük el:

### Bézier-görbe kiszámítása

A `bezier_curve(control_points, t)` függvény a Bézier-görbe egy adott pontját határozza meg a `t ∈ [0, 1]` paraméter alapján. A számítás alapja a **Bernstein-polinomok súlyozott összege**, ahol:

P(t) = ∑(i=0→n) [nCi * (1 - t)^(n-i) * t^i * Pi]

ahol `n` a kontrollpontok száma - 1, `Pi` pedig a kontrollpontok.

### Ütközésdetektálás

A pont és a Bézier-görbe közötti ütközés detektálása az `check_collision()` függvényen keresztül történik. Ez a függvény 1000 pontot mintavételez a görbéről, és azt vizsgálja, hogy a mozgó pont ezek valamelyikéhez **0.1 egységnél** közelebb van-e. Ha igen, a függvény visszaadja az adott `t` paramétert.

### Normálvektor számítása

Ütközés esetén a normálvektor a következőképp kerül kiszámításra:

- Két közeli görbepont (`P(t)` és `P(t+Δt)`) különbsége adja a tangens irányt.
- A normálvektor erre merőleges, azaz `[-tangens_y, tangens_x]`, majd egységvektorrá normáljuk.

### Sebesség visszaverése

A sebesség visszaverése az alábbi képlet szerint történik:

v' = (v - 2 * (v • n) * n) * 0.9

ahol `v` az eredeti sebesség, `n` a normálvektor. A `0.9`-es szorzó a visszapattanás **csillapítását** szimulálja.

### Funkcionalitás
- **Zárt Bézier-görbe:** A kontrollpontok segítségével van meghatározva, és a görbének a zárt jellege miatt a görbe kezdőpontja és végpontja egybeesik.
- **Görbe kirajzolása:** Az alkalmazás képes kirajzolni a Bézier-görbét, valamint annak belső területét egy halvány kék színnel.
- **Pattogó pont:** A mozgó pont egy egyszerű animációban "pattog" a Bézier-görbén belül. Az ütközéskor a pont sebessége tükröződik a görbével való érintkezéskor.

## Használt Technológiák
A projekt a következő technológiák felhasználásával készült:

- **Python:** A fejlesztéshez Python programozási nyelvet választottam.
- **matplotlib:** A grafikai megjelenítéshez és animációhoz használtam, különösen a Bézier-görbe kirajzolásához és az animáció megvalósításához.
- **numpy:** A számításokhoz, vektor műveletekhez és a pontos geometriai algoritmusokhoz használtam.