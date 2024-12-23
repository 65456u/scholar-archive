#include "../../include/Lexer.h"
void Lexer::commentHandler(int first, std::ostream &os) {
    int c;
    std::istream &is = this->istream;
    pLexer::StringBuffer buffer;
    while ((c = is.peek()) != EOF) {
        if (c == '\n') {
            break;
        } else {
            getNextChar();
            buffer.push_back(c);
        }
    }
    std::string content = std::string(buffer.begin(), buffer.end());
    os << "COMMENT\t" << content << std::endl;
}