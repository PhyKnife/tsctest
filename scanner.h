#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>

enum class TokenType {
    Identifier,
    Integer,
    String,
    EndOfFile,
    Error
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

class Scanner {
public:
    Scanner(const std::string& source);
    Token scan();

private:
    bool is_whitespace(char ch);
    bool is_digit(char ch);
    bool is_alpha(char ch);

    void skip_whitespace();
    Token make_token(TokenType type);
    Token scan_number();
    Token scan_identifier();
    Token scan_string();

    std::string source;
    size_t index;
    int line;
    int column;
};

#endif // SCANNER_H