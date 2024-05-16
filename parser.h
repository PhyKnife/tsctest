// parser.h
#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "ast.h"
#include <vector>
#include <memory>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    ExprPtr parse();

private:
    const std::vector<Token>& tokens;
    int current;

    bool isAtEnd();
    Token advance();
    Token peek();
    Token previous();
    bool match(TokenType type);
    Token consume(TokenType type, const std::string& message);
    
    ExprPtr expression();
    ExprPtr primary();
    ExprPtr binaryOp(ExprPtr left, int precedence);
    int getPrecedence();
};

#endif // PARSER_H
