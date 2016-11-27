#include "gtest/gtest.h"

#include "memcached_text_protocol_parser.h"

#include <memory>

using std::make_shared;


TEST(StorageCommandTests, ValidSet) {
    const shared_ptr<string> payload = make_shared<string>("set blah 3 0 11\r\nHello World\r\n");

    MemcachedTextProtocol::Parser parser(payload);
}

TEST(StorageCommandTests, InValidSet) {
    const shared_ptr<string> payload = make_shared<string>("set\r\n");

    ASSERT_THROW(MemcachedTextProtocol::Parser parser(payload), MemcachedTextProtocol::ParserException);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
