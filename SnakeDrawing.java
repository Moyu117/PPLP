import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.Line2D;
import java.awt.geom.Path2D;
import java.awt.geom.Point2D;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 * 演示如何从 txt 文件中读取顶点、边、面，并在 Swing 面板上画出形状
 */
public class SnakeDrawing extends JPanel {

    // 1) 存储所有顶点
    private final List<Point2D.Double> allPoints = new ArrayList<>();

    // 2) 存储所有边：每条边就是 Line2D
    private final List<Line2D.Double> edges = new ArrayList<>();

    // 3) 存储所有面：每个面是一个多边形，由若干顶点 (x, y) 组成
    private final List<List<Point2D.Double>> faces = new ArrayList<>();

    // 全局最小、最大坐标，用于后续坐标变换
    private double minX = Double.MAX_VALUE;
    private double maxX = Double.MIN_VALUE;
    private double minY = Double.MAX_VALUE;
    private double maxY = Double.MIN_VALUE;

    /**
     * 构造函数
     *
     * @param sommetFile  顶点文件，如 sommets.txt
     * @param aretesFile  边文件，如 aretes.txt
     * @param facesFile   面文件，如 faces.txt
     */
    public SnakeDrawing(String sommetFile, String aretesFile, String facesFile) {
        readSommetFile(sommetFile);
        readAretesFile(aretesFile);
        readFacesFile(facesFile);
    }

    /**
     * 读取 sommet.txt，示例格式：
     * 4495                    // 点的总数(可用可不用)
     * 21 ( 5.28082, -0.185735)
     * 21 ( 5.21956, -0.185334)
     * ...
     */
    private void readSommetFile(String fileName) {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {

            // 1) 读第一行(若是点数)
            String line = br.readLine();
            int totalPoints = Integer.parseInt(line.trim());

            // 2) 后面每行解析
            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) {
                    continue;
                }
                // 例："21 ( 5.28082, -0.185735)"
                int start = line.indexOf('(');
                int end = line.indexOf(')');
                if (start >= 0 && end > start) {
                    String coord = line.substring(start + 1, end).trim();
                    // "5.28082, -0.185735"
                    String[] xy = coord.split(",");
                    if (xy.length == 2) {
                        double x = Double.parseDouble(xy[0]);
                        double y = Double.parseDouble(xy[1]);

                        allPoints.add(new Point2D.Double(x, y));

                        // 更新全局范围
                        minX = Math.min(minX, x);
                        maxX = Math.max(maxX, x);
                        minY = Math.min(minY, y);
                        maxY = Math.max(maxY, y);
                    }
                }
            }

            System.out.println("读取 sommet.txt 完毕，共解析到 " + allPoints.size() + " 个点");
            if (allPoints.size() != totalPoints) {
                System.out.println("警告：解析的点数量与第一行声明的数量不一致！");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 读取 aretes.txt，示例格式：
     * 6483
     * 47   ( 5.28082, -0.185735)  ( 5.30811, -0.185161)
     * 47   ( 5.25019, -0.185534)  ( 5.28082, -0.185735)
     * ...
     */
    private void readAretesFile(String fileName) {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            // 先读一行(总边数)
            String line = br.readLine();
            int totalEdges = Integer.parseInt(line.trim());

            // 后续每行
            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) {
                    continue;
                }
                // 例子："47   ( 5.28082, -0.185735)  ( 5.30811, -0.185161)"
                String[] parts = line.split("\\)");
                // parts[0] -> "47   ( 5.28082, -0.185735"
                // parts[1] -> "  ( 5.30811, -0.185161"

                if (parts.length >= 2) {
                    Point2D.Double p1 = extractPointFromString(parts[0]);
                    Point2D.Double p2 = extractPointFromString(parts[1]);
                    if (p1 != null && p2 != null) {
                        edges.add(new Line2D.Double(p1, p2));
                    }
                }
            }

            System.out.println("读取 aretes.txt 完毕，共解析到 " + edges.size() + " 条边");
            if (edges.size() != totalEdges) {
                System.out.println("警告：解析的边数量与第一行声明的数量不一致！");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 解析 faces.txt，每行格式举例：
     * 1989                              // 面的总数(可用可不用)
     * 111 5 ( 5.30811, -0.185161) ( 5.30838, -0.157988) ( 5.29301, -0.157887) ( 5.25019, -0.185534) ( 5.28082, -0.185735)
     * 135 6 ( 5.25019, -0.185534) ( 5.29301, -0.157887) ( 5.25088, -0.0752674) ( 5.19344, -0.0912184) ( 5.18981, -0.174538) ( 5.21956, -0.185334)
     * ...
     */
    private void readFacesFile(String fileName) {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            // 读第一行(如果是面数量，比如 1989)
            String line = br.readLine();
            // 例如： int totalFaces = Integer.parseInt(line.trim());

            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) {
                    continue;
                }
                // 例："111 5 ( 5.30811, -0.185161) ( 5.30838, -0.157988) ..."

                // 切割
                String[] parts = line.split("\\(");
                // parts[0] ~ "111 5 "
                // parts[1..n] 均是坐标

                if (parts.length < 2) {
                    continue;
                }
                // 解析前两个数字(如果有)
                String[] headNums = parts[0].trim().split("\\s+");
                // headNums[0] -> "111", headNums[1] -> "5"
                int faceId = Integer.parseInt(headNums[0]); // face 的标识(可不用)
                int vertexCount = Integer.parseInt(headNums[1]);

                // 存储该面的所有顶点
                List<Point2D.Double> facePoints = new ArrayList<>();

                // 后面每段都是一个顶点(带或不带右括号)
                for (int i = 1; i < parts.length; i++) {
                    // 如 " 5.30811, -0.185161)"
                    String seg = parts[i];
                    // 去掉右括号
                    int endParen = seg.indexOf(')');
                    if (endParen >= 0) {
                        seg = seg.substring(0, endParen);
                    }
                    seg = seg.trim(); // "5.30811, -0.185161"
                    String[] xy = seg.split(",");
                    if (xy.length == 2) {
                        double x = Double.parseDouble(xy[0]);
                        double y = Double.parseDouble(xy[1]);

                        facePoints.add(new Point2D.Double(x, y));

                        // 更新全局 min/max
                        minX = Math.min(minX, x);
                        maxX = Math.max(maxX, x);
                        minY = Math.min(minY, y);
                        maxY = Math.max(maxY, y);
                    }
                }

                // 可简单校验顶点数量
                if (facePoints.size() != vertexCount) {
                    System.err.println("警告：面 " + faceId + " 解析到 " + facePoints.size()
                            + " 个顶点，但声明的是 " + vertexCount + " 个");
                }

                // 加入 faces 列表
                faces.add(facePoints);
            }

            System.out.println("读取 faces.txt 完毕，共解析到 " + faces.size() + " 个面。");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 从形如 "47   ( 5.28082, -0.185735" 的片段中提取 (x, y)
     */
    private Point2D.Double extractPointFromString(String str) {
        int start = str.indexOf('(');
        if (start < 0) {
            return null;
        }
        String coord = str.substring(start + 1).trim(); // "5.28082, -0.185735"
        String[] xy = coord.split(",");
        if (xy.length == 2) {
            try {
                double x = Double.parseDouble(xy[0]);
                double y = Double.parseDouble(xy[1]);
                return new Point2D.Double(x, y);
            } catch (NumberFormatException e) {
                e.printStackTrace();
            }
        }
        return null;
    }

    /**
     * 绘制
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2 = (Graphics2D) g;
        // 打开反锯齿
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

        int w = getWidth();
        int h = getHeight();

        // 数据范围
        double dataWidth = maxX - minX;
        double dataHeight = maxY - minY;
        if (dataWidth <= 0 || dataHeight <= 0) {
            return; // 防止异常
        }

        // 让 x 和 y 同比例缩放
        double scale = Math.min(w / dataWidth, h / dataHeight);

        // 把 (minX, minY) 映射到 (0,0) 后再缩放，然后再居中
        // 计算居中偏移
        double offsetX = (w - dataWidth * scale) / 2.0;
        double offsetY = (h - dataHeight * scale) / 2.0;

        // ===== 1) 先画边 =====
        g2.setColor(Color.BLACK);
        for (Line2D.Double edge : edges) {
            double x1 = edge.x1 - minX;
            double y1 = edge.y1 - minY;
            double x2 = edge.x2 - minX;
            double y2 = edge.y2 - minY;

            x1 *= scale;
            y1 *= scale;
            x2 *= scale;
            y2 *= scale;

            // 翻转 y
            y1 = (dataHeight * scale) - y1;
            y2 = (dataHeight * scale) - y2;

            // 居中
            x1 += offsetX;
            y1 += offsetY;
            x2 += offsetX;
            y2 += offsetY;

            g2.draw(new Line2D.Double(x1, y1, x2, y2));
        }

        // ===== 2) 再画面 =====
        // 给面设定一个半透明红色(仅示例)，你可根据需求修改
        g2.setColor(new Color(255, 0, 0, 80));

        for (List<Point2D.Double> face : faces) {
            Path2D.Double path = new Path2D.Double();
            boolean first = true;

            for (Point2D.Double rawP : face) {
                double x = (rawP.x - minX) * scale;
                double y = (rawP.y - minY) * scale;
                y = (dataHeight * scale) - y;
                x += offsetX;
                y += offsetY;

                if (first) {
                    path.moveTo(x, y);
                    first = false;
                } else {
                    path.lineTo(x, y);
                }
            }
            path.closePath();
            // 填充该多边形
            g2.fill(path);
            // 或者如果你只想画轮廓，可以用 g2.draw(path);
        }
    }

    /**
     * main 测试
     */
    public static void main(String[] args) {
        // 下面写成相对路径，前提是你在 IDE 里把工作目录设置为包含 txt 文件的文件夹
        // 也可直接写绝对路径，如 "C:/User/xxx/sommets.txt"
        String sommetFile = "src/sommets.txt";
        String aretesFile = "src/aretes.txt";
        String facesFile  = "src/faces.txt";

        SnakeDrawing panel = new SnakeDrawing(sommetFile, aretesFile, facesFile);

        JFrame frame = new JFrame("Snake Drawing Demo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1000, 700);
        frame.setLocationRelativeTo(null);
        frame.add(panel);
        frame.setVisible(true);
    }
}
