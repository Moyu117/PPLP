import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.List;

public class DrawingFrame extends Frame {

    private final List<Shape2D> shapes = new ArrayList<>();
    private static final double BASE_SCALE_FACTOR = 30.0; // 基础放大倍数（比如 2 倍、3 倍）

    public DrawingFrame(String title) {
        super(title);
        setSize(800, 600);
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
        setVisible(true);
    }

    public void addShape(Shape2D shape) {
        synchronized (shapes) {
            shapes.add(shape);
        }
        repaint();
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        int width = getWidth();
        int height = getHeight();
        int centerX = width / 2;
        int centerY = height / 2;

        // **计算随窗口变化的 SCALE_FACTOR**
        double scaleX = (width / 200.0) * BASE_SCALE_FACTOR;
        double scaleY = (height / 200.0) * BASE_SCALE_FACTOR;
        double SCALE_FACTOR = Math.min(scaleX, scaleY); // 保持比例不变

        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // **绘制坐标系**
        g2.setColor(Color.LIGHT_GRAY);
        g2.drawLine(0, centerY, width, centerY); // X轴
        g2.drawLine(centerX, 0, centerX, height); // Y轴

        final List<Shape2D> snapshot;
        synchronized (shapes) {
            snapshot = new ArrayList<>(shapes);
        }

        if (snapshot.isEmpty()) {
            return;
        }

        for (Shape2D s : snapshot) {
            g2.setColor(parseColor(s.color));
            switch (s.type) {
                case POINT:
                    drawPoint(g2, s.xs[0], s.ys[0], centerX, centerY, SCALE_FACTOR);
                    break;
                case SEGMENT:
                    drawSegment(g2, s.xs, s.ys, centerX, centerY, SCALE_FACTOR);
                    break;
                case CERCLE:
                    drawCircle(g2, s.xs, s.ys, centerX, centerY, SCALE_FACTOR);
                    break;
                case POLYGONE:
                    drawPolygon(g2, s.xs, s.ys, centerX, centerY, SCALE_FACTOR);
                    break;
            }
        }
    }

    private void drawPoint(Graphics g, double x, double y, int centerX, int centerY, double scaleFactor) {
        int px = (int) (centerX + x * scaleFactor);
        int py = (int) (centerY - y * scaleFactor);
        g.fillOval(px, py, 1, 1); // 保持点大小为 1x1
    }

    private void drawSegment(Graphics g, double[] xs, double[] ys, int centerX, int centerY, double scaleFactor) {
        g.drawLine(
                (int) (centerX + xs[0] * scaleFactor), (int) (centerY - ys[0] * scaleFactor),
                (int) (centerX + xs[1] * scaleFactor), (int) (centerY - ys[1] * scaleFactor)
        );
    }

    private void drawCircle(Graphics g, double[] xs, double[] ys, int centerX, int centerY, double scaleFactor) {
        double cx = xs[0] * scaleFactor;
        double r = xs[1] * scaleFactor;
        double cy = ys[0] * scaleFactor;

        int left = (int) (centerX + cx - r);
        int top = (int) (centerY - cy - r);
        int diam = (int) (2 * r);
        g.drawOval(left, top, diam, diam);
    }

    private void drawPolygon(Graphics g, double[] xs, double[] ys, int centerX, int centerY, double scaleFactor) {
        int n = xs.length;
        int[] xPoints = new int[n];
        int[] yPoints = new int[n];
        for (int i = 0; i < n; i++) {
            xPoints[i] = (int) (centerX + xs[i] * scaleFactor);
            yPoints[i] = (int) (centerY - ys[i] * scaleFactor);
        }
        g.drawPolygon(xPoints, yPoints, n);
    }

    private Color parseColor(String col) {
        if (col == null) return Color.GRAY;
        switch (col.toLowerCase()) {
            case "red":
                return Color.RED;
            case "green":
                return Color.GREEN;
            case "blue":
                return Color.BLUE;
            case "cyan":
                return Color.CYAN;
            case "yellow":
                return Color.YELLOW;
            case "black":
                return Color.BLACK;
            default:
                return Color.GRAY;
        }
    }
}
