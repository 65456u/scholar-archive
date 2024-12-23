cmake_minimum_required(VERSION 3.22)
project(SimplePythonLexer)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimplePythonLexer src/main.cpp
        src/data.cpp
        src/utils.cpp
        src/Lexer.cpp
        src/handlers/digitHandler.cpp
        src/handlers/alphaHandler.cpp
        src/handlers/punctuationHandler.cpp
        src/handlers/stringHandler.cpp
        src/handlers/commentHandler.cpp
        src/LexerException.cpp
        include/LexerException.h
)
