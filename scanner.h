// scanner.h
#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

// 定义了一系列的token类型
enum class TokenType {
    KEYWORD, IDENTIFIER, NUMBER, STRING, OPERATOR, SEPARATOR, COMMENT, UNKNOWN, END_OF_FILE
};

// 定义了Token的数据结构，包括类型、值、行号和列号
struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

// 扫描器类
class Scanner {
public:
    // 构造函数，接收源代码字符串
    Scanner(const std::string& source);
    // 扫描源代码，返回一系列的token
    std::vector<Token> scanTokens();

private:
    std::string source; // 源代码字符串
    std::vector<Token> tokens; // token列表
    int start; // 当前正在扫描的token的起始位置
    int current; // 当前正在扫描的字符的位置
    int line; // 当前正在扫描的行号
    int column; // 当前正在扫描的列号

    // 判断是否已经扫描完所有的字符
    bool isAtEnd();
    // 读取下一个字符，并将current向前移动一位
    char advance();
    // 创建一个新的token，并将其添加到tokens列表中
    void addToken(TokenType type, const std::string& value = "");
    // 查看下一个字符，但不移动current
    char peek();
    // 扫描下一个token
    void scanToken();
    // 扫描一个标识符
    void scanIdentifier();
    // 扫描一个数字
    void scanNumber();
    // 扫描一个字符串
    void scanString();
    // 跳过空白字符
    void skipWhitespace();
    // 跳过注释
    void skipComment();
};

#endif // SCANNER_H
