# Lexical Analysis

Lexical analysis is the first phase of the ChatFlow language processing. It involves breaking down the source code into tokens, which are the smallest meaningful units of the language. The lexer, also known as the tokenizer, scans the source code character by character and groups them into tokens based on predefined patterns and rules.

## Comment

In ChatFlow, comments are denoted by a hash character (`#`) followed by the comment text. They can be used to provide explanations, document the code, or temporarily disable specific parts of the flow. Comments in ChatFlow are ignored by the language's interpreter and have no impact on the program's behavior or execution.

For example:

```
flow origin {
    # This is a comment explaining the purpose of this flow
    speak "Hello, world!" # This line speaks a greeting message
    # The following line is commented out to disable its execution
    # listen for name
}
```

In the above example, the comments provide additional information about the flow and the code. The interpreter ignores these comments, ensuring they don't affect the execution of the ChatFlow program.

## Identifiers and Keywords

Identifiers are used to represent names in a programming language. In ChatFlow, an identifier is defined as a sequence of characters that follows a specific pattern.

The pattern for identifiers in ChatFlow is defined using the following BNF notation:

```
IDENTIFIER ::= letter(letter | digit | "_")*
letter ::= "A".."Z" | "a".."z"
digit ::= "0".."9"  
```

An identifier must start with a letter (uppercase or lowercase) or an underscore, followed by zero or more letters, digits, or underscores. This means that identifiers can include a combination of letters (both uppercase and lowercase), digits, and underscores, but they cannot start with a digit.

ChatFlow also has a set of reserved words or keywords that hold special meanings and cannot be used as regular identifiers. It is important to remember that these keywords must be spelled exactly as specified in the ChatFlow language and cannot be used as ordinary identifiers.

Following are the keywords in ChatFlow:

```
flow        if          else        while       speak
engage      handover    end         listen      for
assign      to          true        false       match
equals      larger      than        less        not
timeout     store       fetch
```

## Literals

In ChatFlow, literals are representations of constant values for certain built-in types.

### String Literals

String literals in ChatFlow are represented by sequences of characters enclosed within double quotation marks (`"`). They are used to denote textual data or strings.

The BNF representation is as following:

```
STRING ::= '"' (letter | digit |punctuation)* '"'  
```



For example:

```
"This is a string literal."
"Hello, world!"
"12345"
"Special characters: !@#$%^&*()"
```

String literals are commonly used for storing and manipulating textual data within ChatFlow scripts. They can be assigned to variables, passed as arguments to functions, concatenated, compared, and displayed as output during script execution.

Make sure to enclose string literals within double quotation marks to indicate that they are strings.

### Number Literals

Number literals in ChatFlow are used to represent numeric values, including integers and floating-point numbers.

Here is the BNF representation of number literals in ChatFlow:

```
<NUMBER_LITERAL> ::= <SIGNED_NUMBER>

<SIGNED_NUMBER> ::= ["+" | "-"] <NUMBER>

<NUMBER> ::= <FLOAT> | <INT>  

<FLOAT> ::= <INT> <_EXP> | <DECIMAL> <_EXP>?

<_EXP> ::= ("e" | "E") <SIGNED_INT>

<SIGNED_FLOAT> ::= ["+" | "-"] <FLOAT>  

<DECIMAL> ::= <INT> "." <INT>? | "." <INT> 

<SIGNED_INT> ::= ["+" | "-"] <INT>

<INT> ::= digit+
digit ::= "0"..."9"
```

These rules define the syntax for representing number literals in ChatFlow, allowing for the representation of both integers and floating-point numbers.
