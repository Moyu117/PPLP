public class DrawPointHandler extends RequestHandler {

    public DrawPointHandler(DrawingFrame frame) {
        super(frame);
    }

    @Override
    public void handle(String request) {
        if (request.startsWith("DRAW_POINT")) {
            // Debug日志：确认进入point处理器
            System.out.println("Handling in DrawPointHandler: " + request);

            // 协议：DRAW_POINT x y color
            String[] parts = request.split("\\s+");
            if (parts.length == 4) {
                try {
                    double x = Double.parseDouble(parts[1]);
                    double y = Double.parseDouble(parts[2]);
                    String color = parts[3];

                    Shape2D shape = new Shape2D(ShapeType.POINT, color);
                    shape.xs = new double[] { x };
                    shape.ys = new double[] { y };

                    drawingFrame.addShape(shape);

                } catch (NumberFormatException e) {
                    System.out.println("NumberFormatException in DrawPointHandler: " + e.getMessage());
                }
            }
        } else {
            // 不符合的命令，交给下一个处理器
            super.handle(request);
        }
    }
}
