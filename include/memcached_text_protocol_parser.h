#ifndef MEMCACHED_TEXT_PROTOCOL_PARSER_H
#define MEMCACHED_TEXT_PROTOCOL_PARSER_H

#include <string>
#include <exception>
#include <memory>

using std::string;
using std::exception;
using std::shared_ptr;

namespace MemcachedTextProtocol {
class ParserException : public exception {
public:
    enum ErrorType {
        ERROR,
        CLIENT_ERROR,
        SERVER_ERROR
    };

    ParserException(const ErrorType &errorType, const string &reason = "")
        : errorType(errorType), reason(reason) { }

    /**
     * Convert a ParseException into a response to the client.
     */
    string toResponse() const {
        string response;

        switch(errorType) {
        case ERROR:
            response = "ERROR ";
            break;
        case CLIENT_ERROR:
            response = "CLIENT_ERROR ";
            break;
        case SERVER_ERROR:
            response = "SERVER_ERROR ";
            break;
        }

        response += reason;

        return response;
    }

    virtual const char* what() const noexcept {
        return toResponse().c_str();
    }

private:
    const ErrorType &errorType;
    const string &reason; 
};

/*
 * Storage commands:
 * <command name> <key> <flags> <exptime> <bytes> [noreply]\r\n
 * cas <key> <flags> <exptime> <bytes> <cas unique> [noreply]\r\n
 * 
 * Retrieval commands:
 * get <key>*\r\n
 * gets <key>*\r\n
 */
class Parser {
public:
    /**
     * Constructor that takes in the bytes of the payload
     */
    Parser(const shared_ptr<string> &payload) throw(ParserException);

private:
    const shared_ptr<string> &payload;
    bool is_get;
    string::size_type cmd_end;
    string::size_type key_end;
    string::size_type flags_end;
    string::size_type exp_end;
    string::size_type bytes_end;
    string::size_type cmd_line_end;
};

}

#endif
