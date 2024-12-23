#include "../include/data.h"
void printLiteralTable(std::ostream &ostream, const LiteralTable &literalTable) {
    for (const auto &p: literalTable) {
        switch (p.second) {
            case pLexer::INTEGER_LITERAL:
                ostream << "Integer\t" << std::get<uint64_t>(p.first) << std::endl;
                break;
            case pLexer::FLOAT_LITERAL:
                ostream << "Float\t" << std::get<double>(p.first) << std::endl;
                break;
            case pLexer::IMAGINE_LITERAL:
                ostream << "Imagine\t" << std::get<double>(p.first) << std::endl;
                break;
            case pLexer::STRING_LITERAL:
                ostream << "String\t" << std::get<std::string>(p.first) << std::endl;
                break;
        }
    }
}
