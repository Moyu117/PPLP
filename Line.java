import java.awt.geom.Line2D;
import java.awt.Graphics2D;      // 添加此行
public class Line implements Shape {
    private final double x1, y1, x2, y2;

    public Line(double x1, double y1, double x2, double y2) {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
    }

    @Override
    public void draw(Graphics2D g2d) {
        g2d.draw(new Line2D.Double(x1, y1, x2, y2));
    }
}