#include <iostream>
#include <unordered_set>
#include "../include/utils.h"
void usage(std::ostream &ostream) {
    ostream << "usage: SimplePythonLexer <filename>" << std::endl;
}
bool isWhiteSpace(int c) {
    return c == '\t' || c == ' ' || c == '\r';
}
bool isOct(int c) {
    return c >= '0' && c <= '7';
}
bool isBin(int c) {
    return c == '0' || c == '1';
}
bool isHex(int c) {
    return isdigit(c) or (c >= 'a' && c <= 'f') or (c >= 'A' && c <= 'F');
}
bool isDelimiterChar(int c) {
    const std::string delimiters = "()[],:{};.=@-+*/%!&|^<>~";
    return delimiters.find(char(c)) != std::string::npos;
}

bool isIdentifierContinue(int c) {
    return isalnum(c) or c == '_';
}
bool isValidStringPrefix(const std::string &string) {
    static const std::unordered_set<std::string> validPrefixes = {
            "r", "u", "R", "U", "f", "F",
            "fr", "Fr", "fR", "FR", "rf", "rF", "Rf", "RF",
            ""
    };
    return validPrefixes.find(string) != validPrefixes.end();
}
bool isUnusedChar(int c) {
    return c == '$' or c == '?' or c == '`';
}
bool isValidBytePrefix(const std::string &string) {
    static const std::unordered_set<std::string> validPrefixes = {
            "b", "B",
            "br", "Br", "bR", "BR", "rb", "rB", "Rb", "RB"
    };
    return validPrefixes.find(string) != validPrefixes.end();
}
