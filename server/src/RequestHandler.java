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
     * 责任链的处理逻辑。
     * 如果当前处理器不匹配或处理不了，需要调用 next.handle(request)。
     */
    public void handle(String request) {
        if (next != null) {
            next.handle(request);
        }
    }
}
