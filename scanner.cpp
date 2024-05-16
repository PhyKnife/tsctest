#include "scanner.h"

Scanner::Scanner(const std::string& source)
    : source(source), index(0), line(1), column(1) {}

Token Scanner::scan() {
    skip_whitespace();

    if (index >= source.size()) {
        return make_token(TokenType::EndOfFile);
    }

    char ch = source[index];
    if (is_digit(ch)) {
        return scan_number();
    } else if (is_alpha(ch)) {
        return scan_identifier();
    } else if (ch == '"') {
        return scan_string();
    } else {
        return make_token(TokenType::Error);
    }
}

void Scanner::skip_whitespace() {
    while (index < source.size() && is_whitespace(source[index])) {
        if (source[index] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        index++;
    }
}

Token Scanner::make_token(TokenType type) {
    return {type, "", line, column};
}

Token Scanner::scan_number() {
    size_t start = index;
    while (index < source.size() && is_digit(source[index])) {
        index++;
    }
    return make_token(TokenType::Integer, source.substr(start, index - start));
}

Token Scanner::scan_identifier() {
    size_t start = index;
    while (index < source.size() && is_alpha(source[index]) || is_digit(source[index])) {
        index++;
    }
    return make_token(TokenType::Identifier, source.substr(start, index - start));
}

Token Scanner::scan_string() {
    index++;  // Skip the opening quote
    size_t start = index;
    while (index < source.size() && source[index] != '"') {
        index++;
    }
    if (index == source.size()) {
        return make_token(TokenType::Error);
    }
    index++;  // Skip the closing quote
    return make_token(TokenType::String, source.substr(start + 1, index - start - 2));
}

bool Scanner::is_whitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

bool Scanner::is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool Scanner::is_alpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}