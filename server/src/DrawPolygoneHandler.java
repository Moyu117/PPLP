public class DrawPolygoneHandler extends RequestHandler {

    public DrawPolygoneHandler(DrawingFrame frame) {
        super(frame);
    }

    @Override
    public void handle(String request) {
        if (request.startsWith("DRAW_POLYGONE")) {
            System.out.println("Handling in DrawPolygoneHandler: " + request);

            // 协议: DRAW_POLYGONE n x1 y1 ... xn yn color
            String[] parts = request.split("\\s+");
            if (parts.length >= 3) {
                try {
                    int n = Integer.parseInt(parts[1]);
                    int expectedLength = 2 + 2*n + 1;
                    if (parts.length == expectedLength) {
                        String color = parts[parts.length - 1];
                        double[] xs = new double[n];
                        double[] ys = new double[n];

                        int idx = 2;
                        for (int i = 0; i < n; i++) {
                            xs[i] = Double.parseDouble(parts[idx++]);
                            ys[i] = Double.parseDouble(parts[idx++]);
                        }

                        Shape2D shape = new Shape2D(ShapeType.POLYGONE, color);
                        shape.xs = xs;
                        shape.ys = ys;

                        drawingFrame.addShape(shape);

                    } else {
                        System.out.println("Error in DrawPolygoneHandler: length mismatch. " +
                                "Got " + parts.length + ", expected " + expectedLength);
                    }
                } catch (NumberFormatException e) {
                    System.out.println("NumberFormatException in DrawPolygoneHandler: " + e.getMessage());
                }
            }
        } else {
            super.handle(request);
        }
    }
}
