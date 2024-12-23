#include "../../include/Lexer.h"
void Lexer::punctuationHandler(int first, std::ostream &ostream) {
    std::istream &is = this->istream;
    int next;
    pLexer::StringBuffer buffer;
    pLexer::TokenType tokenType;
    buffer.push_back(first);
    switch (first) {
        case '+':
        case '-':
        case '%':
        case '^':
        case '&':
        case '|':
            next = is.peek();
            if (next == '=') {
                getNextChar();
                buffer.push_back(next);
                tokenType = pLexer::DELIMITER;
            } else {
                if (first == '-' and next == '>') {
                    getNextChar();
                    buffer.push_back(next);
                    tokenType = pLexer::DELIMITER;
                } else {
                    tokenType = pLexer::OPERATOR;
                }
            }
            break;
        case '/':
        case '*':
            next = is.peek();
            if (next == '=') {
                getNextChar();
                buffer.push_back(next);
                tokenType = pLexer::DELIMITER;
            } else if (next == first) {
                getNextChar();
                buffer.push_back(next);
                next = is.peek();
                if (next == '=') {
                    getNextChar();
                    buffer.push_back(next);
                    tokenType = pLexer::DELIMITER;
                } else {
                    tokenType = pLexer::OPERATOR;
                }
            } else {
                tokenType = pLexer::OPERATOR;
            }
            break;
        case '>':
        case '<':
            next = is.peek();
            if (next == '=') {
                getNextChar();
                buffer.push_back(next);
                tokenType = pLexer::OPERATOR;
            } else if (next == first) {
                getNextChar();
                buffer.push_back(next);
                next = is.peek();
                if (next == '=') {
                    getNextChar();
                    buffer.push_back(next);
                    tokenType = pLexer::DELIMITER;
                } else {
                    tokenType = pLexer::OPERATOR;
                }
            } else {
                tokenType = pLexer::OPERATOR;
            }
            break;
        case '@':
        case '=':
        case ':':
            next = is.peek();
            if (next == '=') {
                getNextChar();
                buffer.push_back(next);
                tokenType = pLexer::OPERATOR;
            } else {
                tokenType = pLexer::DELIMITER;
            }
            break;
        case '(':
        case ')':
        case ',':
        case '.':
        case ';':
        case '[':
        case ']':
        case '{':
        case '}':
            tokenType = pLexer::DELIMITER;
            break;
        case '!':
            next = is.peek();
            if (next == '=') {
                getNextChar();
                buffer.push_back(next);
                tokenType = pLexer::OPERATOR;
            } else {
                throw LexerException(pLexer::PUNCTUATION_ERROR, "Invalid Punctuation a");
            }
            break;
        case '~':
            tokenType = pLexer::OPERATOR;
            break;
        default:
            throw LexerException(pLexer::PUNCTUATION_ERROR, "Invalid Punctuation b");
    }
    std::string content = std::string(buffer.begin(), buffer.end());
    std::unordered_map<std::string, std::string> stringMap;
    std::string typeName;
    if (tokenType == pLexer::DELIMITER) {
        delimiterCount ++;
        stringMap = pythonDelimiters;
        typeName = "Delimiter";
    } else {
        operatorCount ++;
        stringMap = pythonOperators;
        typeName = "Operator";
    }
    auto t = stringMap.find(content);
    if (t != stringMap.end()) {
        ostream << typeName << '\t' << t->second << std::endl;
    } else {
        throw LexerException(pLexer::PUNCTUATION_ERROR, "Invalid Punctuation d");
    }
    if (content == ",") {
        this->lineJoin = true;
    } else {
        this->lineJoin = false;
    }
    this->wordCount ++;
}
