import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Ellipse2D;
import java.util.ArrayList;
import java.util.List;

public class DrawingFrame extends Frame {

    private final List<Shape2D> shapes = new ArrayList<>();
    private int centerX, centerY; // 画布中心点（坐标原点）
    private boolean fillShapes = false; // **默认不填充**

    public DrawingFrame(String title) {
        super(title);
        setSize(800, 600);

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        // **按 F 键切换填充模式**
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyChar() == 'f') {
                    fillShapes = !fillShapes;
                    repaint();
                }
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
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // 计算画布中心点
        centerX = getWidth() / 2;
        centerY = getHeight() / 2;

        // **绘制坐标轴**
        drawAxes(g2);

        synchronized (shapes) {
            if (shapes.isEmpty()) {
                System.out.println("No shapes to draw.");
                return;
            }

            for (Shape2D s : shapes) {
                g2.setColor(parseColor(s.color));
                switch (s.type) {
                    case POINT:
                        drawPoint(g2, s.xs[0], s.ys[0]);
                        break;
                    case SEGMENT:
                        drawSegment(g2, s.xs, s.ys);
                        break;
                    case CERCLE:
                        drawCircle(g2, s.xs, s.ys, s.color);
                        break;
                    case POLYGONE:
                        drawPolygon(g2, s.xs, s.ys, s.color);
                        break;
                }
            }
        }
    }

    /**
     * **绘制坐标轴**
     */
    private void drawAxes(Graphics2D g2) {
        g2.setColor(Color.GRAY);
        g2.drawLine(0, centerY, getWidth(), centerY); // X 轴
        g2.drawLine(centerX, 0, centerX, getHeight()); // Y 轴

        // 标记轴的方向
        g2.drawString("+X", getWidth() - 20, centerY - 5);
        g2.drawString("-X", 10, centerY - 5);
        g2.drawString("+Y", centerX + 5, 15);
        g2.drawString("-Y", centerX + 5, getHeight() - 10);
    }

    private void drawPoint(Graphics g, double x, double y) {
        int px = (int) toScreenX(x);
        int py = (int) toScreenY(y);
        g.fillOval(px - 2, py - 2, 4, 4); // **确保点的中心对齐**
    }

    private void drawSegment(Graphics2D g2, double[] xs, double[] ys) {
        double x1 = toScreenX(xs[0]);
        double y1 = toScreenY(ys[0]);
        double x2 = toScreenX(xs[1]);
        double y2 = toScreenY(ys[1]);

        g2.drawLine((int) x1, (int) y1, (int) x2, (int) y2);
    }

    private void drawCircle(Graphics2D g2, double[] xs, double[] ys, String originalColor) {
        double cx = toScreenX(xs[0]);
        double cy = toScreenY(ys[0]);
        double r = xs[1];

        if (fillShapes) {
            // **填充淡蓝色**
            g2.setColor(new Color(173, 216, 230, 150)); // **淡蓝色 + 半透明**
            g2.fill(new Ellipse2D.Double(cx - r, cy - r, 2 * r, 2 * r));
        }

        // **用原本的颜色绘制边框**
        g2.setColor(parseColor(originalColor));
        g2.draw(new Ellipse2D.Double(cx - r, cy - r, 2 * r, 2 * r));
    }

    private void drawPolygon(Graphics2D g2, double[] xs, double[] ys, String originalColor) {
        int n = xs.length;
        int[] xPoints = new int[n];
        int[] yPoints = new int[n];

        for (int i = 0; i < n; i++) {
            xPoints[i] = (int) toScreenX(xs[i]);
            yPoints[i] = (int) toScreenY(ys[i]);
        }

        if (fillShapes) {
            // **填充淡蓝色**
            g2.setColor(new Color(0, 0, 139, 150)); // **淡蓝色 + 半透明**
            g2.fillPolygon(xPoints, yPoints, n);
        }

        // **用原本的颜色绘制边框**
        g2.setColor(parseColor(originalColor));
        g2.drawPolygon(xPoints, yPoints, n);
    }

    private double toScreenX(double x) {
        return centerX + x;  // **确保 x 轴方向正确**
    }

    private double toScreenY(double y) {
        return centerY - y;  // **确保 y 轴翻转**
    }

    private Color parseColor(String col) {
        if (col == null) return Color.GRAY;
        switch (col.toLowerCase()) {
            case "red": return Color.RED;
            case "green": return Color.GREEN;
            case "blue": return Color.BLUE;
            case "cyan": return Color.CYAN;
            case "yellow": return Color.YELLOW;
            case "black": return Color.BLACK;
            default: return Color.GRAY;
        }
    }
}
