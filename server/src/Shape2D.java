/**
 * enregistrez les informations de forme à dessiner : tableau de type (type), de couleur (couleur) et de coordonnées (xs, ys).
 */
public class Shape2D {
    public ShapeType type;
    public String color;
    public double[] xs;
    public double[] ys;

    public Shape2D(ShapeType t, String color) {
        this.type = t;
        this.color = color;
    }
}
