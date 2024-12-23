#include <iostream>
#include <string>
#include <fstream>
#include "../include/utils.h"
#include "../include/Lexer.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        usage(std::cout);
        exit(EXIT_FAILURE);
    }

    std::string filePath = argv[1];
    std::ifstream fileStream(filePath);

    if (! fileStream.is_open()) {
        std::cerr << "Error: Unable to open the file " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    auto lexer = Lexer(fileStream);
    lexer.run(std::cout);

    fileStream.close();

    return 0;
}
