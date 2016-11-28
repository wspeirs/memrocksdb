#include "gtest/gtest.h"

#include "text_protocol_parser.h"

#include <memory>

using std::make_shared;


TEST(StorageCommandTests, ValidSetWithoutNoReply) {
    const shared_ptr<string> payload = make_shared<string>("set blah 3 0 11\r\nHello World\r\n");

    MemcachedTextProtocol::Parser parser(payload);

    ASSERT_FALSE(parser.is_get());
    ASSERT_FALSE(parser.no_reply());

    ASSERT_EQ(parser.get_command(), "set");
    ASSERT_EQ(parser.get_key(), "blah");
    ASSERT_EQ(parser.get_flags(), "3");
    ASSERT_EQ(parser.get_expiration(), 0);
    ASSERT_EQ(parser.get_byte_count(), 11);
    ASSERT_EQ(parser.get_value(), "Hello World");
}

TEST(StorageCommandTests, ValidSetWithNoReply) {
    const shared_ptr<string> payload = make_shared<string>("set blah 3 0 11 noreply\r\nHello World\r\n");

    MemcachedTextProtocol::Parser parser(payload);

    ASSERT_FALSE(parser.is_get());
    ASSERT_TRUE(parser.no_reply());

    ASSERT_EQ(parser.get_command(), "set");
    ASSERT_EQ(parser.get_key(), "blah");
    ASSERT_EQ(parser.get_flags(), "3");
    ASSERT_EQ(parser.get_expiration(), 0);
    ASSERT_EQ(parser.get_byte_count(), 11);
    ASSERT_EQ(parser.get_value(), "Hello World");
}

TEST(StorageCommandTests, ValidGetOneKey) {
    const shared_ptr<string> payload = make_shared<string>("get blah\r\n");

    MemcachedTextProtocol::Parser parser(payload);

    ASSERT_TRUE(parser.is_get());

    ASSERT_EQ(parser.get_keys(), vector<string>({"blah"}));
}

TEST(StorageCommandTests, ValidGetMultipleKey) {
    const shared_ptr<string> payload = make_shared<string>("get foo bar blah\r\n");

    MemcachedTextProtocol::Parser parser(payload);

    ASSERT_TRUE(parser.is_get());

    ASSERT_EQ(parser.get_keys(), vector<string>({"foo", "bar", "blah"}));
}

TEST(StorageCommandTests, ValidGetsOneKey) {
    const shared_ptr<string> payload = make_shared<string>("gets blah\r\n");

    MemcachedTextProtocol::Parser parser(payload);

    ASSERT_TRUE(parser.is_get());

    ASSERT_EQ(parser.get_keys(), vector<string>({"blah"}));
}

TEST(StorageCommandTests, ValidGetsMultipleKey) {
    const shared_ptr<string> payload = make_shared<string>("gets foo bar blah\r\n");

    MemcachedTextProtocol::Parser parser(payload);

    ASSERT_TRUE(parser.is_get());

    ASSERT_EQ(parser.get_keys(), vector<string>({"foo", "bar", "blah"}));
}

TEST(StorageCommandTests, InValidSet) {
    const shared_ptr<string> payload = make_shared<string>("set\r\n");

    ASSERT_THROW(MemcachedTextProtocol::Parser parser(payload), MemcachedTextProtocol::ParserException);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
