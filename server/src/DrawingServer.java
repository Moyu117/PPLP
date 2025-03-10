import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.IOException;

public class DrawingServer {
    private int port;
    private DrawingFrame drawingFrame;
    private RequestHandler chain;

    public DrawingServer(int port) {
        this.port = port;
        // creer AWT Frame
        drawingFrame = new DrawingFrame("AWT Frame Drawing Demo");

        // construire une chaîne de responsabilité
        RequestHandler pointHandler   = new DrawPointHandler(drawingFrame);
        RequestHandler segHandler     = new DrawSegmentHandler(drawingFrame);
        RequestHandler cercleHandler  = new DrawCercleHandler(drawingFrame);
        RequestHandler polyHandler    = new DrawPolygoneHandler(drawingFrame);

        // connecter
        pointHandler.setNext(segHandler);
        segHandler.setNext(cercleHandler);
        cercleHandler.setNext(polyHandler);

        chain = pointHandler;
    }

    public void start() {
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("DrawingServer started on port " + port);

            while(true) {
                Socket client = serverSocket.accept();
                System.out.println("[SERVER] Client connected: " + client);
                // utliser  thead pour traiter le client
                new Thread(() -> handleClient(client)).start();
            }
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    private void handleClient(Socket client) {
        try(BufferedReader in = new BufferedReader(
                new InputStreamReader(client.getInputStream()));
            PrintWriter out = new PrintWriter(client.getOutputStream(), true))
        {
            String line;
            while((line = in.readLine()) != null) {
                // chaque fois qu'une ligne d'instructions est lue, imprimez-la
                //pour tester
                System.out.println("[SERVER] Received line: " + line);

                // aller chaîne de responsabilité
                chain.handle(line);
            }
        } catch(IOException e) {
            e.printStackTrace();
        } finally {
            try {
                client.close();
            } catch(IOException ignored){}
        }
    }

    public static void main(String[] args) {
        int port = 12345;
        if(args.length > 0) {
            port = Integer.parseInt(args[0]);
        }
        new DrawingServer(port).start();
    }
}
