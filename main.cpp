#include "message_handler.cpp"

int main() {
    MessageHandler messageHandler;

    messageHandler.HandleMessage("asdf");
    messageHandler.HandleMessage("print I'm taeguk.");
    messageHandler.HandleMessage("start_session Session_1");
    messageHandler.HandleMessage("print I'm taeguk.");
    messageHandler.HandleMessage("asdf");
    messageHandler.HandleMessage("end_session");
    messageHandler.HandleMessage("print better tomorrow");
    messageHandler.HandleMessage("start_session Session_2");
    messageHandler.HandleMessage("print better tomorrow");

    return 0;
}
