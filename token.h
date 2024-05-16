#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#pragma once

enum class TokenType {
    Identifier,
    Number,
    String,
    // ...其他Token类型
};

class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(value) {}
};