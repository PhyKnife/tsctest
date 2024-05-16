// parser.cpp
#include "parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) 
    : tokens(tokens), current(0) {}

ExprPtr Parser::parse() {
    return expression();
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current - 1];
}

bool Parser::match(TokenType type) {
    if (isAtEnd()) return false;
    if (peek().type != type) return false;
    advance();
    return true;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (match(type)) return previous();
    throw std::runtime_error(message);
}

ExprPtr Parser::expression() {
    return binaryOp(primary(), 0);
}

ExprPtr Parser::primary() {
    if (match(TokenType::NUMBER)) {
        return std::make_shared<NumberExpr>(std::stod(previous().value));
    }
    if (match(TokenType::STRING)) {
        return std::make_shared<StringExpr>(previous().value);
    }
    if (match(TokenType::IDENTIFIER)) {
        return std::make_shared<IdentifierExpr>(previous().value);
    }
    throw std::runtime_error("Expected expression");
}

ExprPtr Parser::binaryOp(ExprPtr left, int precedence) {
    while (!isAtEnd() && getPrecedence() >= precedence) {
        std::string op = advance().value;
        ExprPtr right = primary();
        left = std::make_shared<BinaryExpr>(left, op, right);
    }
    return left;
}

int Parser::getPrecedence() {
    if (isAtEnd()) return -1;
    Token token = peek();
    if (token.type == TokenType::OPERATOR) {
        return 1; // Set appropriate precedence for each operator
    }
    return -1;
}
