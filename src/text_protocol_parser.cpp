#include "memcached_text_protocol_parser.h"


MemcachedTextProtocol::Parser::Parser(const string &payload) throw(ParserException) {
    // search for the command
    auto cmd = payload.find(' ');

    if(cmd == string::npos) {
        throw ParserException(ParserException::ErrorType::ERROR);
    }

    command = string(payload[0], payload[cmd]);
}
