public class DrawCercleHandler extends RequestHandler {

    public DrawCercleHandler(DrawingFrame frame) {
        super(frame);
    }

    @Override
    public void handle(String request) {
        if (request.startsWith("DRAW_CERCLE")) {
            String[] parts = request.split("\\s+");
            if (parts.length == 5) {
                try {
                    double cx = Double.parseDouble(parts[1]);
                    double cy = Double.parseDouble(parts[2]);
                    double r  = Double.parseDouble(parts[3]);
                    String color = parts[4];

                    Shape2D shape = new Shape2D(ShapeType.CERCLE, color);
                    shape.xs = new double[]{ cx, r };
                    shape.ys = new double[]{ cy, 0.0 };

                    drawingFrame.addShape(shape);

                } catch (NumberFormatException e) {
                    System.out.println("Error in DrawCercleHandler: " + e.getMessage());
                }
            }
        } else {
            super.handle(request);
        }
    }
}
