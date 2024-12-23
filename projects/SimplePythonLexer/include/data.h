#ifndef SIMPLE_PYTHON_LEXER_DATA_H
#define SIMPLE_PYTHON_LEXER_DATA_H
#include <iostream>
#include <unordered_map>
#include <variant>
#include <functional>
#include <deque>
#include "enum.h"
namespace pLexer {
    struct VariantHash {
        template<typename T>
        std::size_t operator()(const T &t) const {
            return std::hash<T>{}(t);
        }
    };

    struct VariantEqual {
        template<typename T>
        bool operator()(const T &lhs, const T &rhs) const {
            return lhs == rhs;
        }
    };
    typedef std::deque<int> StringBuffer;
}
class IdentifierTable {
private:
    size_t idCounter = 0;
    std::unordered_map<std::string, size_t> symbolTable;
public:
    size_t insertIdentifier(const std::string &identifier) {
        if (symbolTable.find(identifier) != symbolTable.end()) {
            return symbolTable[identifier];
        } else {
            size_t id = idCounter ++;
            symbolTable[identifier] = id;
            return id;
        }
    }
    void print(std::ostream &ostream = std::cout) {
        for (auto const &itr: symbolTable) {
            auto IdentifierType = (itr.first[0] == '_' ? "Reserved" : "Common");
            ostream << itr.second << '\t' << IdentifierType << '\t' << itr.first << std::endl;
        }
    }
};
typedef std::variant<uint64_t, double, std::string> LiteralValue;
typedef std::unordered_map<LiteralValue, std::size_t, pLexer::VariantHash, pLexer::VariantEqual> LiteralTable;
void printLiteralTable(std::ostream &ostream, const LiteralTable &literalTable);
#endif //SIMPLE_PYTHON_LEXER_DATA_H
