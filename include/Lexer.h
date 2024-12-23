//
// Created by lacuna42 on 2023/10/5.
//

#ifndef SIMPLE_PYTHON_LEXER_LEXER_H
#define SIMPLE_PYTHON_LEXER_LEXER_H

#include <iostream>
#include <unordered_map>
#include "data.h"
#include "utils.h"
#include "enum.h"
#include "LexerException.h"

class Lexer {
public:
    explicit Lexer(std::istream &istream) : istream(istream) {}
    void run(std::ostream &ostream);
    void printSummary(std::ostream &ostream);
private:
    std::istream &istream;
    IdentifierTable identifierTable;
    LiteralTable literalTable;
    size_t currentRow = 1;
    size_t currentCol = 1;
    size_t characterCount = 0;
    size_t keywordCount = 0;
    size_t identifierCount = 0;
    size_t delimiterCount = 0;
    size_t operatorCount = 0;
    size_t wordCount = 0;
    size_t logicalLineCount = 0;
    bool lineJoin = false;
    void commentHandler(int first, std::ostream &os);
    void digitHandler(int first, std::ostream &os);
    void alphaHandler(int first, std::ostream &ostream);
    void punctuationHandler(int first, std::ostream &ostream);
    void stringHandler(int first, std::ostream &ostream, const std::string &stringPrefix = "");
    int getNextChar();
};
#endif //SIMPLE_PYTHON_LEXER_LEXER_H
