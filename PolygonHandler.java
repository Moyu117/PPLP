import javax.swing.*;
import java.util.List;

public class PolygonHandler implements CommandHandler {
    private CommandHandler next;
    private final List<Shape> shapes;
    private final JPanel panel;

    public PolygonHandler(List<Shape> shapes, JPanel panel) {
        this.shapes = shapes;
        this.panel = panel;
    }

    @Override
    public void handle(String command) {
        if (command.startsWith("POLYGON")) {
            String[] parts = command.split(" ");
            PolygonShape polygon = new PolygonShape();
            for (int i = 1; i < parts.length; i++) {
                String[] coord = parts[i].split(",");
                double x = Double.parseDouble(coord[0]);
                double y = Double.parseDouble(coord[1]);
                polygon.addPoint(x, y);
            }
            shapes.add(polygon);
        } else if (next != null) {
            next.handle(command);
        }
    }

    @Override
    public void setNext(CommandHandler next) {
        this.next = next;
    }
}