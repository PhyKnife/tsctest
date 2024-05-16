// parser.cpp
#include "parser.h"
#include "scanner.h"
#include <stdexcept>

// 构造函数，初始化token列表和当前处理的token的位置
Parser::Parser(const std::vector<Token>& tokens) 
    : tokens(tokens), current(0) {}

// 解析token，生成一系列的表达式
std::vector<ExprPtr> Parser::parse() {
    std::vector<ExprPtr> statements;
    while (!isAtEnd()) {
        statements.push_back(variableDeclaration());
    }
    return statements;
}

// 判断是否已经处理完所有的token
bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

// 读取下一个token，并将current向前移动一位
Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

// 查看下一个token，但不移动current
Token Parser::peek() {
    return tokens[current];
}

// 获取上一个token
Token Parser::previous() {
    return tokens[current - 1];
}

// 检查下一个token的类型是否匹配给定的类型
bool Parser::match(TokenType type) {
    if (isAtEnd()) return false;
    if (peek().type != type) return false;
    advance();
    return true;
}

// 消耗一个token，如果token的类型不匹配给定的类型，报错
Token Parser::consume(TokenType type, const std::string& message) {
    if (match(type)) return previous();
    throw std::runtime_error(message);
}

// 解析一个表达式
ExprPtr Parser::expression() {
    return binaryOp(primary(), 0);
}

// 解析一个基础表达式（例如数字、字符串、标识符）
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

// 解析一个二元操作表达式（例如加法、减法、乘法、除法）
ExprPtr Parser::binaryOp(ExprPtr left, int precedence) {
    while (!isAtEnd() && getPrecedence() >= precedence) {
        std::string op = advance().value;
        ExprPtr right = primary();
        left = std::make_shared<BinaryExpr>(left, op, right);
    }
    return left;
}

// 获取当前token对应的二元操作的优先级
int Parser::getPrecedence() {
    if (isAtEnd()) return -1;
    Token token = peek();
    if (token.type == TokenType::OPERATOR) {
        return 1; // Set appropriate precedence for each operator
    }
    return -1;
}

// 解析一个变量声明
ExprPtr Parser::variableDeclaration() {
    if (match(TokenType::IDENTIFIER)) {
        std::string name = previous().value;
        if (match(TokenType::OPERATOR) && previous().value == "=") {
            ExprPtr initializer = expression();
            return std::make_shared<BinaryExpr>(
                std::make_shared<IdentifierExpr>(name), "=", initializer
            );
        }
    }
    throw std::runtime_error("Expected variable declaration");
}