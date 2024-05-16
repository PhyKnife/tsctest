#include "scanner.h"
#include <iostream>

int main() {
    std::string input = "var a = 123; \"Hello, World!\";";
    Scanner scanner(input);
    Token token = scanner.scan();

    while (token.type != TokenType::EndOfFile) {
        std::cout << "Token: " << static_cast<int>(token.type) << ", Value: " << token.value
                  << ", Line: " << token.line << ", Column: " << token.column << std::endl;
        token = scanner.scan();
    }

    return 0;
}