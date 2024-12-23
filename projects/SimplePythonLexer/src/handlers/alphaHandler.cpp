#include "../../include/Lexer.h"
void Lexer::alphaHandler(int first, std::ostream &ostream) {
    int c;
    pLexer::StringBuffer buffer;
    buffer.push_back(first);
    std::istream &is = this->istream;
    while ((c = is.peek()) != EOF) {
        if (isWhiteSpace(c) or isDelimiterChar(c)) {
            break;
        } else if (isIdentifierContinue(c)) {
            buffer.push_back(c);
            getNextChar();
        } else if (c == '\'' or c == '\"') {
            std::string prefix = std::string(buffer.begin(), buffer.end());
            stringHandler(getNextChar(), ostream, prefix);
            return;
        } else {
            throw LexerException(pLexer::IDENTIFIER_ERROR, "Invalid Identifier");
        }
    }
    std::string name = std::string(buffer.begin(), buffer.end());
    if (pythonKeywords.find(name) != pythonKeywords.end()) {
        ostream << "Keyword\t" << name << std::endl;
        this->keywordCount ++;
    } else {
        auto id = this->identifierTable.insertIdentifier(name);
        auto mark = (name[0] == '_') ? "Reserved" : "Common";
        ostream << "Identifier\t" << name << '\t' << id << '\t' << mark << std::endl;
        this->identifierCount ++;
    }
    this->wordCount++;
}
