// scanner.h
#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

enum class TokenType {
    KEYWORD, IDENTIFIER, NUMBER, STRING, OPERATOR, SEPARATOR, COMMENT, UNKNOWN, END_OF_FILE
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
    std::vector<Token> scanTokens();

private:
    std::string source;
    std::vector<Token> tokens;
    int start;
    int current;
    int line;
    int column;

    bool isAtEnd();
    char advance();
    void addToken(TokenType type, const std::string& value = "");
    char peek();
    void scanToken();
    void scanIdentifier();
    void scanNumber();
    void scanString();
    void skipWhitespace();
    void skipComment();
};

#endif // SCANNER_H
