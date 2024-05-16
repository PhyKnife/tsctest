// scanner.cpp
#include "scanner.h"
#include <cctype>

// 构造函数，初始化源代码字符串、当前位置、行号和列号
Scanner::Scanner(const std::string& source) 
    : source(source), start(0), current(0), line(1), column(0) {}

// 扫描源代码，生成token列表
std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) { // 当还有字符未扫描时，继续扫描
        start = current;
        scanToken();
    }
    // 添加一个表示文件结束的token
    tokens.push_back({TokenType::END_OF_FILE, "", line, column});
    return tokens;
}

// 判断是否已经扫描完所有的字符
bool Scanner::isAtEnd() {
    return current >= source.length();
}

// 读取下一个字符，并将current向前移动一位
char Scanner::advance() {
    current++;
    column++;
    return source[current - 1];
}

// 创建一个新的token，并将其添加到tokens列表中
void Scanner::addToken(TokenType type, const std::string& value) {
    tokens.push_back({type, value, line, column});
}

// 查看下一个字符，但不移动current
char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

// 扫描下一个token
void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::SEPARATOR, "("); break;
        case ')': addToken(TokenType::SEPARATOR, ")"); break;
        // ... 处理其他单字符token
        default:
            if (std::isalpha(c) || c == '_') { // 如果是字母或下划线，扫描一个标识符
                scanIdentifier();
            } else if (std::isdigit(c)) { // 如果是数字，扫描一个数字
                scanNumber();
            } else if (c == '\"') { // 如果是引号，扫描一个字符串
                scanString();
            } else if (std::isspace(c)) { // 如果是空白字符，跳过
                skipWhitespace();
            } else { // 如果是其他字符，生成一个未知类型的token
                addToken(TokenType::UNKNOWN, std::string(1, c));
            }
            break;
    }
}

// 扫描一个标识符
void Scanner::scanIdentifier() {
    while (std::isalnum(peek()) || peek() == '_') advance(); // 如果是字母、数字或下划线，继续读取
    std::string value = source.substr(start, current - start);
    // 检查标识符是否是关键字
    addToken(TokenType::IDENTIFIER, value);
}

// 扫描一个数字
void Scanner::scanNumber() {
    while (std::isdigit(peek())) advance(); // 如果是数字，继续读取
    std::string value = source.substr(start, current - start);
    addToken(TokenType::NUMBER, value);
}

// 扫描一个字符串
void Scanner::scanString() {
    while (peek() != '\"' && !isAtEnd()) { // 如果不是引号并且还有字符未扫描，继续读取
        advance();
    }
    if (isAtEnd()) { // 如果已经扫描完所有的字符，但没有找到字符串的结束引号，处理未结束的字符串错误
        return;
    }
    advance(); // 跳过结束引号
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

// 跳过空白字符
void Scanner::skipWhitespace() {
    while (std::isspace(peek())) { // 如果是空白字符，跳过
        if (peek() == '\n') { // 如果是换行符，行号加一，列号重置为0
            line++;
            column = 0;
        }
        advance();
    }
}

// 跳过注释
void Scanner::skipComment() {
    while (peek() != '\n' && !isAtEnd()) advance(); // 如果不是换行符并且还有字符未扫描，继续读取
}