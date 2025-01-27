import java.awt.Graphics2D;      // 添加此行
import java.awt.geom.Path2D;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;

public class PolygonShape implements Shape {
    private final List<Point2D.Double> points = new ArrayList<>();

    public void addPoint(double x, double y) {
        points.add(new Point2D.Double(x, y));
    }

    @Override
    public void draw(Graphics2D g2d) {
        if (points.isEmpty()) return;

        Path2D path = new Path2D.Double();
        Point2D.Double first = points.get(0);
        path.moveTo(first.x, first.y);
        for (Point2D.Double p : points) {
            path.lineTo(p.x, p.y);
        }
        path.closePath();
        g2d.draw(path);
    }
}