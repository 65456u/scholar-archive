#include "../include/LexerException.h"
void LexerException::print(std::ostream &ostream, size_t currentRow, size_t currentCol) {
    switch (this->errorType) {
        case pLexer::NUMBER_ERROR:
            ostream << "Numeric Error at " << currentRow << ':' << currentCol << ':' << this->message << std::endl;
            break;
        case pLexer::STRING_ERROR:
            ostream << "String Error at " << currentRow << ':' << currentCol << ':' << this->message << std::endl;
            break;
        case pLexer::IDENTIFIER_ERROR:
            ostream << "Identifier Error at " << currentRow << ':' << currentCol << ':' << this->message << std::endl;
            break;
        case pLexer::PUNCTUATION_ERROR:
            ostream << "Punctuation Error at " << currentRow << ':' << currentCol << ':' << this->message << std::endl;
            break;
        case pLexer::CHAR_ERROR:
            ostream << "Character Error at " << currentRow << ':' << currentCol << ':' << this->message << std::endl;
            break;
    }
}
