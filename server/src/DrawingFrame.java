import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;

public class DrawingFrame extends Frame {

    private final List<Shape2D> shapes = new ArrayList<>();
    private static final double BASE_SCALE_FACTOR = 100; // 直接放大 20 倍
    private static final int INIT_WIDTH = 800;
    private static final int INIT_HEIGHT = 600;

    private int offsetX = 0;
    private int offsetY = 0;
    private int lastMouseX, lastMouseY;
    private boolean showOnlyVertices = false; // 只显示顶点
    private boolean fillPolygons = false; // 是否填充图形内部空白区域

    public DrawingFrame(String title) {
        super(title);
        setSize(INIT_WIDTH, INIT_HEIGHT);

        // **鼠标拖拽功能**
        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                lastMouseX = e.getX();
                lastMouseY = e.getY();
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                int dx = e.getX() - lastMouseX;
                int dy = e.getY() - lastMouseY;
                offsetX += dx;
                offsetY += dy;

                lastMouseX = e.getX();
                lastMouseY = e.getY();

                repaint();
            }
        });

        // **键盘快捷键**
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyChar() == 'v') { // 按 'v' 只显示顶点
                    showOnlyVertices = !showOnlyVertices;
                    repaint();
                } else if (e.getKeyChar() == 'f') { // 按 'f' 填充空白区域
                    fillPolygons = !fillPolygons;
                    repaint();
                }
            }
        });

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
        int centerX = width / 2 + offsetX;
        int centerY = height / 2 + offsetY;

        double scaleX = (width / (double) INIT_WIDTH) * BASE_SCALE_FACTOR;
        double scaleY = (height / (double) INIT_HEIGHT) * BASE_SCALE_FACTOR;
        double SCALE_FACTOR = Math.min(scaleX, scaleY);

        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // **绘制坐标轴**
        g2.setColor(Color.LIGHT_GRAY);
        g2.drawLine(0, centerY, width, centerY);
        g2.drawLine(centerX, 0, centerX, height);

        final List<Shape2D> snapshot;
        synchronized (shapes) {
            snapshot = new ArrayList<>(shapes);
        }

        if (snapshot.isEmpty()) {
            return;
        }

        for (Shape2D s : snapshot) {
            switch (s.type) {
                case POINT:
                    g2.setColor(parseColor(s.color));
                    drawPoint(g2, s.xs[0], s.ys[0], centerX, centerY, SCALE_FACTOR);
                    break;
                case SEGMENT:
                    if (!showOnlyVertices) {
                        g2.setColor(parseColor(s.color));
                        drawSegment(g2, s.xs, s.ys, centerX, centerY, SCALE_FACTOR);
                    }
                    break;
                case CERCLE:
                    g2.setColor(parseColor(s.color));
                    drawCircle(g2, s.xs, s.ys, centerX, centerY, SCALE_FACTOR);
                    break;
                case POLYGONE:
                    drawPolygon(g2, s, centerX, centerY, SCALE_FACTOR);
                    break;
            }
        }
    }

    private void drawPoint(Graphics g, double x, double y, int centerX, int centerY, double scaleFactor) {
        int px = (int) (centerX + x * scaleFactor);
        int py = (int) (centerY - y * scaleFactor);
        g.fillOval(px, py, 1, 1);
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

    private void drawPolygon(Graphics g, Shape2D s, int centerX, int centerY, double scaleFactor) {
        int n = s.xs.length;
        int[] xPoints = new int[n];
        int[] yPoints = new int[n];

        for (int i = 0; i < n; i++) {
            xPoints[i] = (int) (centerX + s.xs[i] * scaleFactor);
            yPoints[i] = (int) (centerY - s.ys[i] * scaleFactor);
        }

        if (fillPolygons) {
            g.setColor(Color.BLUE); // 仅填充内部
            g.fillPolygon(xPoints, yPoints, n);
        }

        // **保持原始边框颜色**
        if (!showOnlyVertices) {
            g.setColor(parseColor(s.color));
            g.drawPolygon(xPoints, yPoints, n);
        }

        // **如果启用了“只显示顶点”模式**
        if (showOnlyVertices) {
            g.setColor(parseColor(s.color)); // 保持点的颜色
            for (int i = 0; i < n; i++) {
                g.fillOval(xPoints[i], yPoints[i], 1, 1);
            }
        }
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
