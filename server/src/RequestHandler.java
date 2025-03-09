public abstract class RequestHandler {
    protected RequestHandler next;
    protected DrawingFrame drawingFrame;

    public RequestHandler(DrawingFrame frame) {
        this.drawingFrame = frame;
    }

    public void setNext(RequestHandler next) {
        this.next = next;
    }

    /**
     * la logique de traitement de la chaine de responsabilite.
     * si le processeur actuel ne correspond pas ou ne peut pas le gérer, il doit appeler next.handle(request)
     */
    public void handle(String request) {
        if (next != null) {
            next.handle(request);
        }
    }
}
