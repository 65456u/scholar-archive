# ChatFlow

ChatFlow is a domain-specific language designed specifically for authoring conversational dialog flows, such as for chatbots and voice assistants. It provides an easy-to-read and write syntax that models natural conversations, with abstractions for common constructs needed for conversational interfaces. 

## Key Features

- **Readability**: ChatFlow syntax reads like natural language to enable non-programmers to understand and author dialog flows.
- **Easy to use**: The specialized DSL provides high-level abstractions tailored for conversations like dialog flows, conditional logic, variables, etc., making chatbot development intuitive.
- **Integration**: ChatFlow provides rich integration capabilities with external systems via Python. It allows data processing in real-time during the conversation. Users can define custom execution flows named "tributary," which enable integration with anything in Python, including databases, APIs, and more.
- **Integration with Python's async functionality**: ChatFlow enables asynchronous, non-blocking execution of dialogs via Python's async/await model. This allows I/O operations like API calls to run in parallel without blocking during a conversation.
- **Interpreted**: ChatFlow scripts are interpreted at runtime, enabling rapid prototyping. The interpreter provides early detection of errors in conversational logic during testing without needing compilation.
- **Extensible**: Users can extend ChatFlow functionality by calling out to Python code within dialog scripts. This allows adding advanced or custom processing logic when needed.

## Quick Start

Check our [quick start guide](https://65456u.github.io/ChatFlow/quick-start/) to get started with ChatFlow.

For detailed examples and tutorials, refer to the [ChatFlow documentation](https://65456u.github.io/ChatFlow/).

## License

ChatFlow is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Acknowledgements

ChatFlow owes much gratitude to the open-source projects that helped make it possible. In particular:

- **Lark**: ChatFlow builds on the excellent [Lark](https://github.com/lark-parser/lark) parsing toolkit for generating the abstract syntax tree from the Conversation Flow scripts. The ability to define a clean grammar and easily parse it into a manipulatable tree structure is invaluable.

## Contributing

We welcome contributions to ChatFlow! If you find a bug, have a feature request, or want to contribute code, please open an issue or submit a pull request on the [GitHub repository](https://github.com/65456u/ChatFlow).

## Contact

For any questions or inquiries, please contact us at yanghongchen@bupt.edu.cn.