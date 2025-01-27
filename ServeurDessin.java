import java.util.ArrayList;       // 添加此行
import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.net.*;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class ServeurDessin {
    private static final List<Shape> shapes = new CopyOnWriteArrayList<>();
    private static DrawingPanel panel;

    public static void main(String[] args) throws IOException {
        JFrame frame = new JFrame("Drawing Server");
        panel = new DrawingPanel();
        frame.add(panel);
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);

        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(() -> handleClient(clientSocket)).start();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try {
            List<Shape> tempShapes = new ArrayList<>();
            CommandHandler lineHandler = new LineHandler(tempShapes, panel);
            CommandHandler polygonHandler = new PolygonHandler(tempShapes, panel);
            lineHandler.setNext(polygonHandler);

            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            String command;
            while ((command = in.readLine()) != null) {
                lineHandler.handle(command);
            }
            shapes.addAll(tempShapes);
            SwingUtilities.invokeLater(panel::repaint);
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static class DrawingPanel extends JPanel {
        private static final double SCALE_FACTOR = 50.0; // 缩放因子（根据坐标范围调整）
        private static final int OFFSET_X = 400;        // 水平偏移（窗口中心）
        private static final int OFFSET_Y = 300;        // 垂直偏移（窗口中心）

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;

            // 启用抗锯齿
            g2d.setRenderingHint(
                    RenderingHints.KEY_ANTIALIASING,
                    RenderingHints.VALUE_ANTIALIAS_ON
            );

            // 坐标系变换
            g2d.translate(OFFSET_X, OFFSET_Y);       // 平移到窗口中心
            g2d.scale(SCALE_FACTOR, -SCALE_FACTOR);  // 缩放并翻转Y轴

            // 绘制所有图形
            for (Shape shape : shapes) {
                shape.draw(g2d);
            }
        }
    }
}