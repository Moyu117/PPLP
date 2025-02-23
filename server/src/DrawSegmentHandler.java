public class DrawSegmentHandler extends RequestHandler {

    public DrawSegmentHandler(DrawingFrame frame) {
        super(frame);
    }

    @Override
    public void handle(String request) {
        if (request.startsWith("DRAW_SEGMENT")) {
            String[] parts = request.split("\\s+");
            if (parts.length == 6) {
                try {
                    double x1 = Double.parseDouble(parts[1]);
                    double y1 = Double.parseDouble(parts[2]);
                    double x2 = Double.parseDouble(parts[3]);
                    double y2 = Double.parseDouble(parts[4]);
                    String color = parts[5];

                    Shape2D shape = new Shape2D(ShapeType.SEGMENT, color);
                    shape.xs = new double[] { x1, x2 };
                    shape.ys = new double[] { y1, y2 };

                    drawingFrame.addShape(shape);

                } catch (NumberFormatException e) {
                    System.out.println("Error in DrawSegmentHandler: " + e.getMessage());
                }
            }
        } else {
            super.handle(request);
        }
    }
}
