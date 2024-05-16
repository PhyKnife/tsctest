// ast.h
#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>

struct Expr {
    virtual ~Expr() = default;
    virtual void print(int indent = 0) const = 0;
};

using ExprPtr = std::shared_ptr<Expr>;

struct NumberExpr : Expr {
    double value;
    NumberExpr(double value) : value(value) {}
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "NumberExpr(" << value << ")\n";
    }
};

struct StringExpr : Expr {
    std::string value;
    StringExpr(const std::string& value) : value(value) {}
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "StringExpr(\"" << value << "\")\n";
    }
};

struct IdentifierExpr : Expr {
    std::string name;
    IdentifierExpr(const std::string& name) : name(name) {}
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "IdentifierExpr(" << name << ")\n";
    }
};

struct BinaryExpr : Expr {
    ExprPtr left;
    std::string op;
    ExprPtr right;
    BinaryExpr(ExprPtr left, const std::string& op, ExprPtr right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "BinaryExpr(\n";
        left->print(indent + 2);
        std::cout << std::string(indent + 2, ' ') << "Operator(" << op << ")\n";
        right->print(indent + 2);
        std::cout << std::string(indent, ' ') << ")\n";
    }
};

#endif // AST_H
