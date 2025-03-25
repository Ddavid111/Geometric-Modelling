# Geometric-Modelling

**Név:** Drig Dávid  
**Neptun kód:** EZ3YRC

# Féléves Feladat: Zárt Bézier-Görbén Belüli Pattogó Pont

## Feladat Leírása

Implementáljunk egy alkalmazást, amely egy zárt Bézier görbén belül pattogó pontot jelenít meg! Az alkalmazás célja, hogy szimulálja egy pont mozgását a Bézier-görbe által határolt területen, valamint megjelenítse a görbét és annak kitöltött területét. A pont a Bézier-görbével való érintkezéskor tükröződik, szimulálva a fizikai ütközést.

### Funkcionalitás
- **Zárt Bézier-görbe:** A kontrollpontok segítségével van meghatározva, és a görbének a zárt jellege miatt a görbe kezdőpontja és végpontja egybeesik.
- **Görbe kirajzolása:** Az alkalmazás képes kirajzolni a Bézier-görbét, valamint annak belső területét egy halvány kék színnel.
- **Pattogó pont:** A mozgó pont egy egyszerű animációban "pattog" a Bézier-görbén belül. Az ütközéskor a pont sebessége tükröződik a görbével való érintkezéskor.

## Használt Technológiák
A projekt a következő technológiák felhasználásával készült:

- **Python:** A fejlesztéshez Python programozási nyelvet választottam.
- **matplotlib:** A grafikai megjelenítéshez és animációhoz használtam, különösen a Bézier-görbe kirajzolásához és az animáció megvalósításához.
- **numpy:** A számításokhoz, vektor műveletekhez és a pontos geometriai algoritmusokhoz használtam.