#include "../../include/Lexer.h"
std::unordered_map<pLexer::NumState, std::function<bool(int)>> getCharValidator() {
    std::unordered_map<pLexer::NumState, std::function<bool(int)>> validators;
    validators[pLexer::NUM_BIN] = isBin;
    validators[pLexer::NUM_OCT] = isOct;
    validators[pLexer::NUM_HEX] = isHex;
    return validators;
}
void Lexer::digitHandler(int first, std::ostream &os) {
    pLexer::StringBuffer buffer;
    pLexer::NumState state = pLexer::NUM_START;
    auto isValidChar = getCharValidator();
    if (first == '0') {
        int sign = istream.peek();
        switch (sign) {
            case 'b':
            case 'B':
                state = pLexer::NUM_BIN;
                getNextChar();
                break;
            case 'o':
            case 'O':
                state = pLexer::NUM_OCT;
                getNextChar();
                break;
            case 'x':
            case 'X':
                state = pLexer::NUM_HEX;
                getNextChar();
                break;
            default:
                buffer.push_back(first);
                break;
        }
    } else {
        buffer.push_back(first);
    }
    int c;
    while ((c = istream.peek()) != EOF) {
        if (isdigit(c)) {
            switch (state) {
                case pLexer::NUM_BIN:
                case pLexer::NUM_OCT:
                case pLexer::NUM_HEX: {
                    if (not isValidChar[state](c)) {
                        throw LexerException(pLexer::NUMBER_ERROR, "Invalid Digit");
                    } else {
                        buffer.push_back(c);
                        getNextChar();
                    }
                    break;
                }
                default:
                    buffer.push_back(c);
                    getNextChar();
                    break;
                case pLexer::IN_EXP:
                case pLexer::AFTER_EXP:
                    state = pLexer::LAST_EXP;
                    buffer.push_back(c);
                    getNextChar();
            }
        } else if (c == '_') {
            getNextChar();
        } else if (c == '.') {
            if (state == pLexer::NUM_START) {
                state = pLexer::AFTER_POINT;
                buffer.push_back(c);
                getNextChar();
            } else {
                throw LexerException(pLexer::NUMBER_ERROR, "Redundant dot");
            }
        } else if (c == 'E' or c == 'e') {
            if (state == pLexer::NUM_START or state == pLexer::AFTER_POINT) {
                state = pLexer::AFTER_EXP;
                buffer.push_back(c);
                getNextChar();
            } else {
                throw LexerException(pLexer::NUMBER_ERROR, "Redundant Exponent Mark");
            }
        } else if (c == '+' or c == '-') {
            if (state == pLexer::AFTER_EXP) {
                state = pLexer::IN_EXP;
                buffer.push_back(c);
                getNextChar();
            } else {
                throw LexerException(pLexer::NUMBER_ERROR, "Redundant Operator");
            }
        } else if (c == 'J' or c == 'j') {
            state = pLexer::IMG_FINISH;
            getNextChar();
        } else if (isWhiteSpace(c) or isDelimiterChar(c)) {
            break;
        } else if (isHex(c) and state == pLexer::NUM_HEX) {
            buffer.push_back(c);
            getNextChar();
        } else {
            throw LexerException(pLexer::NUMBER_ERROR, "Invalid Number Format");
        }
    }
    LiteralValue value;
    std::string finalString = std::string(buffer.begin(), buffer.end());
    switch (state) {
        case pLexer::NUM_START:
            value = std::stoull(finalString);
            this->literalTable[value] = pLexer::INTEGER_LITERAL;
            os << "Literal\tInteger\t" << std::get<uint64_t>(value) << std::endl;
            break;
        case pLexer::LAST_EXP:
        case pLexer::AFTER_POINT:
            value = std::stod(finalString);
            this->literalTable[value] = pLexer::FLOAT_LITERAL;
            os << "Literal\tFloat\t" << std::get<double>(value) << std::endl;
            break;
        case pLexer::NUM_BIN:
            value = std::strtoull(finalString.c_str(), nullptr, 2);
            this->literalTable[value] = pLexer::INTEGER_LITERAL;
            os << "Literal\tInteger\t" << std::get<uint64_t>(value) << std::endl;
            break;
        case pLexer::NUM_OCT:
            value = std::strtoull(finalString.c_str(), nullptr, 8);
            this->literalTable[value] = pLexer::INTEGER_LITERAL;
            os << "Literal\tInteger\t" << std::get<uint64_t>(value) << std::endl;
            break;
        case pLexer::NUM_HEX:
            value = std::strtoull(finalString.c_str(), nullptr, 16);
            this->literalTable[value] = pLexer::INTEGER_LITERAL;
            os << "Literal\tInteger\t" << std::get<uint64_t>(value) << std::endl;
            break;
        case pLexer::IMG_FINISH:
            value = std::stod(finalString);
            this->literalTable[value] = pLexer::IMAGINE_LITERAL;
            os << "Literal\t" << "Imagine\t" << std::get<double>(value) << std::endl;
            break;
        case pLexer::AFTER_EXP:
        case pLexer::IN_EXP:
            throw LexerException(pLexer::NUMBER_ERROR, "Number Format");
    }
    this->wordCount ++;
}