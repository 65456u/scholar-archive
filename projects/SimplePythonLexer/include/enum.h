#ifndef SIMPLE_PYTHON_LEXER_ENUM_H
#define SIMPLE_PYTHON_LEXER_ENUM_H
#include <unordered_set>
namespace pLexer {
    typedef enum {
        FLOAT_LITERAL, INTEGER_LITERAL, IMAGINE_LITERAL, STRING_LITERAL, OPERATOR, DELIMITER, BYTE_LITERAL
    } TokenType;
    typedef enum {
        NUMBER_ERROR, STRING_ERROR, IDENTIFIER_ERROR, PUNCTUATION_ERROR, CHAR_ERROR, UNKNOWN_ERROR
    } ErrorType;
    typedef enum {
        NUM_START, AFTER_POINT, NUM_BIN, NUM_OCT, NUM_HEX, AFTER_EXP, IN_EXP, IMG_FINISH, LAST_EXP
    } NumState;

}
enum class Token {
    FALSE, AWAIT, ELSE, IMPORT, PASS,
    NONE, BREAK, EXCEPT, IN, RAISE,
    TRUE, CLASS, FINALLY, IS, RETURN,
    AND, CONTINUE, FOR, LAMBDA, TRY,
    AS, DEF, FROM, NONLOCAL, WHILE,
    ASSERT, DEL, GLOBAL, NOT, WITH,
    ASYNC, ELIF, IF, OR, YIELD
};
static const std::unordered_map<std::string, Token> keywordMap = {
        {"False",    Token::FALSE},
        {"await",    Token::AWAIT},
        {"else",     Token::ELSE},
        {"import",   Token::IMPORT},
        {"pass",     Token::PASS},
        {"none",     Token::NONE},
        {"break",    Token::BREAK},
        {"except",   Token::EXCEPT},
        {"in",       Token::IN},
        {"raise",    Token::RAISE},
        {"True",     Token::TRUE},
        {"class",    Token::CLASS},
        {"finally",  Token::FINALLY},
        {"is",       Token::IS},
        {"return",   Token::RETURN},
        {"and",      Token::AND},
        {"continue", Token::CONTINUE},
        {"for",      Token::FOR},
        {"lambda",   Token::LAMBDA},
        {"try",      Token::TRY},
        {"as",       Token::AS},
        {"def",      Token::DEF},
        {"from",     Token::FROM},
        {"nonlocal", Token::NONLOCAL},
        {"while",    Token::WHILE},
        {"assert",   Token::ASSERT},
        {"del",      Token::DEL},
        {"global",   Token::GLOBAL},
        {"not",      Token::NOT},
        {"with",     Token::WITH},
        {"async",    Token::ASYNC},
        {"elif",     Token::ELIF},
        {"if",       Token::IF},
        {"or",       Token::OR},
        {"yield",    Token::YIELD}
};

static const std::unordered_map<std::string, std::string> pythonDelimiters = {
        {"+",   "PLUS"},
        {"-",   "MINUS"},
        {"(",   "LEFT_PARENTHESIS"},
        {")",   "RIGHT_PARENTHESIS"},
        {"[",   "LEFT_BRACKET"},
        {"]",   "RIGHT_BRACKET"},
        {"{",   "LEFT_CURLY_BRACE"},
        {"}",   "RIGHT_CURLY_BRACE"},
        {",",   "COMMA"},
        {":",   "COLON"},
        {".",   "DOT"},
        {";",   "SEMICOLON"},
        {"@",   "AT_SIGN"},
        {"=",   "EQUALS"},
        {"->",  "ARROW"},
        {"+=",  "PLUS_EQUALS"},
        {"-=",  "MINUS_EQUALS"},
        {"*=",  "TIMES_EQUALS"},
        {"/=",  "DIVIDE_EQUALS"},
        {"//=", "FLOOR_DIVIDE_EQUALS"},
        {"%=",  "MODULO_EQUALS"},
        {"@=",  "AT_EQUALS"},
        {"&=",  "BITWISE_AND_EQUALS"},
        {"|=",  "BITWISE_OR_EQUALS"},
        {"^=",  "BITWISE_XOR_EQUALS"},
        {">>=", "RIGHT_SHIFT_EQUALS"},
        {"<<=", "LEFT_SHIFT_EQUALS"},
        {"**=", "POWER_EQUALS"}
};
static const std::unordered_map<std::string, std::string> pythonOperators = {
        {"+",  "PLUS"},
        {"-",  "MINUS"},
        {"*",  "TIMES"},
        {"**", "POWER"},
        {"/",  "DIVIDE"},
        {"//", "FLOOR_DIVIDE"},
        {"%",  "MODULO"},
        {"@",  "AT_SIGN"},
        {"<<", "LEFT_SHIFT"},
        {">>", "RIGHT_SHIFT"},
        {"&",  "BITWISE_AND"},
        {"|",  "BITWISE_OR"},
        {"^",  "BITWISE_XOR"},
        {"~",  "BITWISE_NOT"},
        {":=", "WALRUS_OPERATOR"},
        {"<",  "LESS_THAN"},
        {">",  "GREATER_THAN"},
        {"<=", "LESS_THAN_OR_EQUAL"},
        {">=", "GREATER_THAN_OR_EQUAL"},
        {"==", "EQUALS"},
        {"!=", "NOT_EQUALS"}
};
static const std::unordered_set<std::string> pythonKeywords = {
        "False", "await", "else", "import", "pass",
        "None", "break", "except", "in", "raise",
        "True", "class", "finally", "is", "return",
        "and", "continue", "for", "lambda", "try",
        "as", "def", "from", "nonlocal", "while",
        "assert", "del", "global", "not", "with",
        "async", "elif", "if", "or", "yield"
};
#endif //SIMPLE_PYTHON_LEXER_ENUM_H
