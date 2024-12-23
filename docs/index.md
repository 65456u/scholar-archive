## Introduction

ChatFlow is a domain-specific language designed specifically for authoring conversational dialog flows, such as for chatbots and voice assistants. 

It provides an easy to read and write syntax that models natural conversations, with abstractions for common constructs needed for conversational interfaces. ChatFlow makes it simpler for non-programmers to define complex conversational experiences.

The language can integrate tightly with Python enabling advanced functionality when required through custom code. ChatFlow aims to balance simplicity with versatility. 

## Key Features  

- **Readability**: ChatFlow syntax reads like natural language to enable non-programmers to understand and author dialog flows.

- **Easy to use**: The specialized DSL provides high-level abstractions tailored for conversations like dialog flows, conditional logic, variables, etc. making chatbot development intuitive.

- **Integration**: ChatFlow provides rich integration capabilities with external systems via Python. It allows data processing in real-time during the conversation. Users can define custom execution flows named "tributary", which enable integration with anything in Python including databases, APIs and more.

- **Integration with python's async functionality**: ChatFlow enables asynchronous, non-blocking execution of dialogs via Python's async/await model. This allows I/O operations like API calls to run in parallel without blocking during a conversation.  

- **Interpreted**: ChatFlow scripts are interpreted at runtime, enabling rapid prototyping. The interpreter provides early detection of errors in conversational logic during testing without needing compilation.

- **Extensible**: Users can extend ChatFlow functionality by calling out to Python code within dialog scripts. This allows adding advanced or custom processing logic when needed.


## Learning ChatFlow

1. [Quick Start](tutorials.md)
2. [Tutorial](tutorials.md)
3. [Grammar](grammar.md)


## Acknowledgements

ChatFlow owes much gratitude to the open source projects that helped make it possible.

In particular:

- **Lark**  
    ChatFlow builds on the excellent [Lark parsing toolkit](https://github.com/lark-parser/lark) for generating the abstract syntax tree from the Conversation Flow scripts. The ability to define a clean grammar and easily parse it into a manipulatable tree structure is invaluable.

## License

Lark uses the [MIT license](LICENSE.md).
