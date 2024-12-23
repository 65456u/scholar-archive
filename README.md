# Simple Python Lexer

This is a C++ implementation of a simple Python lexer.

## Build

```shell
mkdir build
cd build
cmake ..
make
```

## Run

```shell
SimplePythonLexer <filename>
```

## Features

The lexer handles the following Python language elements:

- **Comments:** Both single-line and multi-line comments are recognized.
- **Identifiers:** Recognizes variable names and function names.
- **Literals:** Handles integers, floats, imaginary numbers, and strings.
- **Delimiters:** Recognizes various delimiters like parentheses, braces, and commas.
- **Operators:** Identifies common Python operators like +, -, *, /, etc.

The lexer provides a summary including:

- Total characters processed.
- Count of delimiters.
- Count of operators.
- Literal table displaying recognized literal values.
- Identifier table displaying recognized identifiers.

Additionally, the lexer can identify common lexical errors such as invalid numbers, strings, etc., and provides helpful error messages.
