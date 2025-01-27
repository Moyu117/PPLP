public interface CommandHandler {
    void handle(String command);
    void setNext(CommandHandler next);
}