import javax.swing.*;
import java.util.List;

public class LineHandler implements CommandHandler {
    private CommandHandler next;
    private final List<Shape> shapes;
    private final JPanel panel;

    public LineHandler(List<Shape> shapes, JPanel panel) {
        this.shapes = shapes;
        this.panel = panel;
    }

    @Override
    public void handle(String command) {
        if (command.startsWith("LINE")) {
            String[] parts = command.split(" ");
            String[] start = parts[1].split(",");
            String[] end = parts[2].split(",");
            double x1 = Double.parseDouble(start[0]);
            double y1 = Double.parseDouble(start[1]);
            double x2 = Double.parseDouble(end[0]);
            double y2 = Double.parseDouble(end[1]);
            shapes.add(new Line(x1, y1, x2, y2));
        } else if (next != null) {
            next.handle(command);
        }
    }

    @Override
    public void setNext(CommandHandler next) {
        this.next = next;
    }
}