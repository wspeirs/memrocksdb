#include "gtest/gtest.h"

#include "memcached_text_protocol_parser.h"


TEST(StorageCommandTests, ValidSet) {
    const string payload = "set blah 3 0 11\r\nHello World\r\n";

    MemcachedTextProtocol::Parser parser(payload);
}

TEST(StorageCommandTests, InValidSet) {
    const string payload = "set\r\n";

    ASSERT_THROW(MemcachedTextProtocol::Parser parser(payload), MemcachedTextProtocol::ParserException);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
