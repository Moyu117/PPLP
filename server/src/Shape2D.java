/**
 * 记录要绘制的形状信息：类型(type)、颜色(color)以及坐标(xs, ys)数组
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
