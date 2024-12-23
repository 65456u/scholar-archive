#ifndef SIMPLE_PYTHON_LEXER_UTILS_H
#define SIMPLE_PYTHON_LEXER_UTILS_H
#include <iostream>
void usage(std::ostream &ostream);
bool isWhiteSpace(int c);
bool isOct(int c);
bool isBin(int c);
bool isHex(int c);
bool isDelimiterChar(int c);
bool isIdentifierContinue(int c);
bool isValidStringPrefix(const std::string &string);
bool isValidBytePrefix(const std::string &string);
bool isUnusedChar(int c);
#endif