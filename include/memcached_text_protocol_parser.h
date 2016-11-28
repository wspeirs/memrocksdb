#ifndef MEMCACHED_TEXT_PROTOCOL_PARSER_H
#define MEMCACHED_TEXT_PROTOCOL_PARSER_H

#include <string>
#include <exception>
#include <memory>
#include <cstdint>

using std::string;
using std::exception;
using std::shared_ptr;
using std::stoi;

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

    inline bool is_get() const {
        return _is_get;
    }

    inline string get_command() const {
        return string(*payload, 0, cmd_end);
    }

    inline string get_key() const {
        return string(*payload, cmd_end+1, key_end-cmd_end-1);
    }

    inline string get_flags() const {
        return string(*payload, key_end+1, flags_end-key_end-1);
    }

    inline uint64_t get_expiration() const {
        return stoi(string(*payload, flags_end+1, exp_end-flags_end-1), nullptr);
    }

    inline uint64_t get_bytes() const {
        return stoi(string(*payload, exp_end+1, bytes_end-exp_end-1), nullptr);
    }

private:
    const shared_ptr<string> &payload;
    bool _is_get;
    string::size_type cmd_end;
    string::size_type key_end;
    string::size_type flags_end;
    string::size_type exp_end;
    string::size_type bytes_end;
    string::size_type cmd_line_end;
};

}

#endif
