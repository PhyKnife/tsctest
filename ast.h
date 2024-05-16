// ast.h
#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>

// 表达式基类
struct Expr {
    virtual ~Expr() = default;
    // 打印表达式的方法，indent参数表示缩进的空格数
    virtual void print(int indent = 0) const = 0;
};

// 表达式指针类型，使用shared_ptr进行内存管理
using ExprPtr = std::shared_ptr<Expr>;

// 数字表达式类，表示一个数字
struct NumberExpr : Expr {
    double value; // 数字的值
    NumberExpr(double value) : value(value) {} // 构造函数
    // 打印数字表达式
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "NumberExpr(" << value << ")\n";
    }
};

// 字符串表达式类，表示一个字符串
struct StringExpr : Expr {
    std::string value; // 字符串的值
    StringExpr(const std::string& value) : value(value) {} // 构造函数
    // 打印字符串表达式
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "StringExpr(\"" << value << "\")\n";
    }
};

// 标识符表达式类，表示一个标识符
struct IdentifierExpr : Expr {
    std::string name; // 标识符的名称
    IdentifierExpr(const std::string& name) : name(name) {} // 构造函数
    // 打印标识符表达式
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "IdentifierExpr(" << name << ")\n";
    }
};

// 二元表达式类，表示一个二元操作（例如加法、减法、乘法、除法）
struct BinaryExpr : Expr {
    ExprPtr left; // 左操作数
    std::string op; // 操作符
    ExprPtr right; // 右操作数
    BinaryExpr(ExprPtr left, const std::string& op, ExprPtr right)
        : left(std::move(left)), op(op), right(std::move(right)) {} // 构造函数
    // 打印二元表达式
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "BinaryExpr(\n";
        left->print(indent + 2); // 打印左操作数
        std::cout << std::string(indent + 2, ' ') << "Operator(" << op << ")\n"; // 打印操作符
        right->print(indent + 2); // 打印右操作数
        std::cout << std::string(indent, ' ') << ")\n";
    }
};

#endif // AST_H
