#ifndef SIMPLE_PYTHON_LEXER_LEXER_EXCEPTION_H
#define SIMPLE_PYTHON_LEXER_LEXER_EXCEPTION_H
#include <exception>
#include <string>
#include "../include/Lexer.h"
#include "../include/enum.h"

class LexerException : public std::exception {
private:
    std::string message;
    pLexer::ErrorType errorType;
public:
    LexerException(pLexer::ErrorType errorType, const std::string &message) {
        this->errorType = errorType;
        this->message = message;
    }
    void print(std::ostream &ostream, size_t currentRow, size_t currentCol);
};

#endif //SIMPLE_PYTHON_LEXER_LEXER_EXCEPTION_H
