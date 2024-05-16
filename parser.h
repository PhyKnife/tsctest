// parser.h
#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "ast.h"
#include <vector>
#include <memory>

// 解析器类
class Parser {
public:
    // 构造函数，接收一系列的token
    Parser(const std::vector<Token>& tokens);
    // 解析token，生成抽象语法树（AST）
    std::vector<ExprPtr> parse();

private:
    const std::vector<Token>& tokens; // token列表
    int current; // 当前正在处理的token的位置

    // 判断是否已经处理完所有的token
    bool isAtEnd();
    // 读取下一个token，并将current向前移动一位
    Token advance();
    // 查看下一个token，但不移动current
    Token peek();
    // 获取上一个token
    Token previous();
    // 检查下一个token的类型是否匹配给定的类型
    bool match(TokenType type);
    // 消耗一个token，如果token的类型不匹配给定的类型，报错
    Token consume(TokenType type, const std::string& message);
    
    // 解析一个表达式
    ExprPtr expression();
    // 解析一个基础表达式（例如字面量、变量、括号表达式）
    ExprPtr primary();
    // 解析一个二元操作表达式（例如加法、减法、乘法、除法）
    ExprPtr binaryOp(ExprPtr left, int precedence);
    // 获取当前token对应的二元操作的优先级
    int getPrecedence();
    // 解析一个变量声明
    ExprPtr variableDeclaration();
};

#endif // PARSER_H