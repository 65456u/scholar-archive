#include "../../include/Lexer.h"
void Lexer::stringHandler(int first, std::ostream &ostream, const std::string &stringPrefix) {
    pLexer::TokenType literalType;
    if (isValidStringPrefix(stringPrefix)) {
        literalType = pLexer::STRING_LITERAL;
    } else if (isValidBytePrefix(stringPrefix)) {
        literalType = pLexer::BYTE_LITERAL;
    } else {
        throw LexerException(pLexer::STRING_ERROR, "Invalid Prefix");
    }
    std::istream &is = this->istream;
    int c;
    pLexer::StringBuffer buffer;
    buffer.push_back(first);
    while ((c = is.peek()) != EOF) {
        getNextChar();
        buffer.push_back(c);
        if (c == first) {
            break;
        }
    }
    if (buffer.back() != first) {
        throw LexerException(pLexer::STRING_ERROR, "Unclosed String");
    }
    std::string content = stringPrefix + std::string(buffer.begin(), buffer.end());
    this->literalTable[content] = literalType;
    ostream << "Literal\t" << "String\t" << content << std::endl;
    this->wordCount ++;
}
