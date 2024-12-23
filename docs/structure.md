# Structure of ChatFlow Program

The structure of a ChatFlow program is based on three key concepts: flow, block, statement, and tributary.

## Flow

A flow in ChatFlow represents a sequence of steps or actions that define the conversational logic. It defines the structure and flow of the conversation between the user and the ChatFlow program. A flow is defined using the keyword "flow" followed by a flow name and enclosed within curly braces.

The BNF (Backus-Naur Form) representation of a flow in ChatFlow is as follows:

```
<flow> ::= "flow" <flow_name> "{" <block> "}"
<flow_name> ::= <identifier>
```

In this syntax, the "flow_name" is a user-defined identifier that uniquely identifies the flow within the program. It should be chosen to reflect the purpose or content of the flow. The "block" represents a collection of statements that define the actions and interactions within the flow. These statements can include if statements, speak statements, engage statements, handover statements, and more.

To transition from one flow to another, you can use the engage statement. The engage statement allows you to initiate another flow within the current flow, enabling you to create complex conversation flows and modularize your ChatFlow program. 

To engage a specific flow, you use the following syntax:

```
engage flow_name
```

Here, "flow_name" refers to the name of the flow you want to transition to. By using the engage statement, you can seamlessly navigate between different flows and create dynamic and interactive conversations for your users.

## Block

A block in ChatFlow is a series of statements grouped together within a flow. It represents a section of code that is executed sequentially. A block is enclosed within curly braces and can contain multiple statements.

The definition of a block in ChatFlow can be represented as:

```
<flow> ::= "flow" <flow_name> "{" <block> "}"
```

In this representation, "statement*" denotes zero or more statements within the block. Each statement represents a specific action or instruction within the flow.

When you create a block, any variables declared within that block are only accessible within that block's scope. They are not visible outside of the block or in other blocks within the flow.

Here's an example that demonstrates the usage of a block in ChatFlow:

```chatflow
flow origin {
    # Variables declared within the origin flow block
    assign "John" to name
    assign 25 to age

    # Start of a block
    {
        # Variable declared within the block
        assign "Smith" to lastName

        speak "Full name: " + name + " " + lastName
        speak "Age: " + age
    }  # End of the block

    # The following line will cause an error because lastName is not accessible here
    speak "Last name: " + lastName
}
```

In the above example, the block is defined within the `origin` flow. Inside the block, a variable `lastName` is declared, and the code within the block can access the `name`, `age`, and `lastName` variables. However, outside the block, the `lastName` variable is not accessible, and attempting to access it will result in an error.

By using blocks, you can control the scope of variables and organize your code into logical sections. This allows for better code readability and prevents variable name conflicts between different parts of your ChatFlow program.

## Statement

A statement in ChatFlow is a basic unit of code that represents an action or instruction within a flow. It performs a specific task or interaction with the user. ChatFlow supports various types of statements, including conditionals, speaking to the user, engaging with other flows, listening for user input, assigning values to variables, looping constructs, and more.

The BNF representation of a statement in ChatFlow can be defined as:

```
<statement> ::= <if_statement>
              | <speak_statement>  
              | <engage_statement>
              | <handover_statement>
              | <end_statement>
              | <listen_statement>
              | <assign_statement>
              | <while_statement>  
              | <store_statement>
              | <fetch_statement>
              | "{" <block> "}"
```

Each statement type has its own syntax and purpose within the ChatFlow program.

For more detailed information on statements, please refer to [statement](statement.md).

## Tributary

Tributaries are external functions that can be seamlessly integrated into your ChatFlow program to perform custom operations or interact with external services. They allow you to extend the functionality of ChatFlow by incorporating specific logic or functionality that is not provided by the built-in statements.

To define a tributary in ChatFlow, you can use the `@register_tributary` decorator followed by the tributary name and the function definition. The function should accept the `context`, `speak_function`, and `listen_function` as parameters. The `context` parameter provides access to the ChatFlow context, allowing you to retrieve or modify parameters and other contextual information. The `speak_function` is used to send messages or responses to the user, while the `listen_function` is used to listen for user input.

Here's an example of defining a tributary named "print_parameter" using Python:

```python
@register_tributary("print_parameter")
def display(context, speak_function, listen_function):
    print(context.get_parameter())
```

In this example, the `display` function is registered as the "print_parameter" tributary. Within the function, you have access to the ChatFlow context through the `context` parameter. You can use the `speak_function` to send messages or responses to the user, and the `listen_function` to listen for user input. In this case, the function simply prints the value of a parameter using the `get_parameter()` method of the context.

To use a tributary within your ChatFlow program, you can use the `handover` statement followed by the name of the tributary. This allows you to transfer the conversation to the specified tributary for further processing.

Here's an example of using the `handover` statement to invoke the "display" tributary:

```
handover print_parameter
```

In this example, the `print_parameter` statement transfers the conversation to the "display" tributary, allowing it to perform its specific logic or functionality. Once the tributary has completed its task, the control can be handed back to the ChatFlow program.

By leveraging tributaries, you can integrate external functions or services seamlessly into your ChatFlow program, enhancing its capabilities and enabling custom operations based on your specific requirements.

