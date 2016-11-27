#include "memcached_text_protocol_parser.h"


MemcachedTextProtocol::Parser::Parser(const shared_ptr<string> &payload) throw(ParserException)
    : payload(payload) {
    // search for the command
    cmd_end = payload->find(' ');

    if(cmd_end == string::npos) {
        throw ParserException(ParserException::ErrorType::ERROR);
    }

    // for now only supporting set, add, and get
    if(payload->compare(0, cmd_end, "set") != 0 &&
       payload->compare(0, cmd_end, "add") != 0 &&
       payload->compare(0, cmd_end, "get")) {
        throw ParserException(ParserException::ErrorType::SERVER_ERROR, "Only set, get, and add are supported");
    }

    // check to see if we're handling a get command
    if(payload->compare(0, cmd_end, "get") == 0) {
        is_get = true;
        return;
    }
    
    // must be handling a set/add
    is_get = false;
    
    if(string::npos == (key_end = payload->find(' ', cmd_end))) {
        throw ParserException(ParserException::ErrorType::SERVER_ERROR, "Couldn't find key");
    }

    if(string::npos == (flags_end = payload->find(' ', key_end))) {
        throw ParserException(ParserException::ErrorType::SERVER_ERROR, "Couldn't find flags");
    }

    if(string::npos == (exp_end = payload->find(' ', flags_end))) {
        throw ParserException(ParserException::ErrorType::SERVER_ERROR, "Couldn't find expiration time");
    }

    if(string::npos == (bytes_end = payload->find(' ', exp_end))) {
        throw ParserException(ParserException::ErrorType::SERVER_ERROR, "Couldn't find bytes");
    }

    if(string::npos == (cmd_line_end = payload->find("\r\n", bytes_end))) {
        throw ParserException(ParserException::ErrorType::SERVER_ERROR, "Couldn't find bytes");
    }

}
