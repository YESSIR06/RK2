#include <gtest/gtest.h>
#include <sstream>
#include "message_handler.cpp"

class MessageHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        handler = std::make_unique<MessageHandler>();
    }

    std::unique_ptr<MessageHandler> handler;
};

// Захват вывода std::cout
class CoutRedirect {
public:
    CoutRedirect(std::streambuf* new_buffer) : old(std::cout.rdbuf(new_buffer)) {}
    ~CoutRedirect() { std::cout.rdbuf(old); }
private:
    std::streambuf* old;
};

TEST_F(MessageHandlerTest, HandleInvalidMessage) {
    std::ostringstream oss;
    CoutRedirect redirect(oss.rdbuf());

    handler->HandleMessage("asdf");

    EXPECT_EQ(oss.str(), "\"asdf\" is invalid message.\n");
}

TEST_F(MessageHandlerTest, HandleStartSession) {
    std::ostringstream oss;
    CoutRedirect redirect(oss.rdbuf());

    handler->HandleMessage("start_session Session_1");

    EXPECT_EQ(oss.str(), "[Start Session] Session Name : Session_1\n");
}

TEST_F(MessageHandlerTest, HandlePrintInSession) {
    handler->HandleMessage("start_session Session_1");
    std::ostringstream oss;
    CoutRedirect redirect(oss.rdbuf());

    handler->HandleMessage("print Hello, world!");

    EXPECT_EQ(oss.str(), "[Session_1][Print] Hello, world!\n");
}

TEST_F(MessageHandlerTest, HandleInvalidMessageInSession) {
    handler->HandleMessage("start_session Session_1");
    std::ostringstream oss;
    CoutRedirect redirect(oss.rdbuf());

    handler->HandleMessage("asdf");

    EXPECT_EQ(oss.str(), "[Session_1] \"asdf\" is invalid message.\n");
}

TEST(MessageHandlerTest, HandleEndSession) {
    handler->HandleMessage("start_session Session_1");
    std::ostringstream oss;
    CoutRedirect redirect(oss.rdbuf());

    handler->HandleMessage("end_session");

    EXPECT_EQ(oss.str(), "[Session_1][End Session]\n");
}

TEST_F(MessageHandlerTest, HandlePrintAfterEndSession) {
    handler->HandleMessage("start_session Session_1");
    handler->HandleMessage("end_session");
    std::ostringstream oss;
    CoutRedirect redirect(oss.rdbuf());

    handler->HandleMessage("print After session");

    EXPECT_EQ(oss.str(), "\"print After session\" is invalid message.\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
