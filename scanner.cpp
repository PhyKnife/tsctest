// scanner.cpp
#include "scanner.h"
#include <cctype>

Scanner::Scanner(const std::string& source) 
    : source(source), start(0), current(0), line(1), column(0) {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.push_back({TokenType::END_OF_FILE, "", line, column});
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    current++;
    column++;
    return source[current - 1];
}

void Scanner::addToken(TokenType type, const std::string& value) {
    tokens.push_back({type, value, line, column});
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::SEPARATOR, "("); break;
        case ')': addToken(TokenType::SEPARATOR, ")"); break;
        // ... Handle other single-character tokens
        default:
            if (std::isalpha(c) || c == '_') {
                scanIdentifier();
            } else if (std::isdigit(c)) {
                scanNumber();
            } else if (c == '\"') {
                scanString();
            } else if (std::isspace(c)) {
                skipWhitespace();
            } else {
                addToken(TokenType::UNKNOWN, std::string(1, c));
            }
            break;
    }
}

void Scanner::scanIdentifier() {
    while (std::isalnum(peek()) || peek() == '_') advance();
    std::string value = source.substr(start, current - start);
    // Check if the identifier is a keyword
    addToken(TokenType::IDENTIFIER, value);
}

void Scanner::scanNumber() {
    while (std::isdigit(peek())) advance();
    std::string value = source.substr(start, current - start);
    addToken(TokenType::NUMBER, value);
}

void Scanner::scanString() {
    while (peek() != '\"' && !isAtEnd()) {
        advance();
    }
    if (isAtEnd()) {
        // Handle unterminated string error
        return;
    }
    advance(); // Consume the closing "
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

void Scanner::skipWhitespace() {
    while (std::isspace(peek())) {
        if (peek() == '\n') {
            line++;
            column = 0;
        }
        advance();
    }
}

void Scanner::skipComment() {
    while (peek() != '\n' && !isAtEnd()) advance();
}
