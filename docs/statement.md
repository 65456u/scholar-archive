
## Statements

The ChatFlow statement consists of various types of statements that control the conversation flow and interact with the user.

## If Statement

The if statement in ChatFlow allows you to introduce conditional branching within your conversation flow. It enables you to make decisions based on specific conditions and execute different sets of statements accordingly.

The syntax for the if statement in ChatFlow is as follows:

```
<if_statement> ::= "if" <condition> "{" <block> "}" <else_statement>?

<else_statement> ::= "else" "{" <block> "}"
                  | "else" <if_statement>
```

In this syntax, the "condition" represents an expression that evaluates to a Boolean value. If the condition is true, the statements within the first block are executed. Optionally, an "else" block can be included, which contains statements that are executed when the condition is false. The "else" block can either be a block of statements or another if statement, allowing for nested conditional logic.

## Speak Statement

The speak statement is used to send a message or response to the user during the conversation. It allows you to provide information, ask questions, or guide the user through the interaction.

The syntax for the speak statement in ChatFlow is as follows:

```
<speak_statement> ::= "speak" <str_expression>  

<str_expression> ::= <value> ("+" <value>)*
```

In this syntax, the "str_expression" represents the content of the message to be spoken. It can be a concatenation of multiple values using the "+" operator. The values can be string literals, variable names, or expressions that evaluate to a string.

## Engage Statement

The engage statement in ChatFlow allows you to transition from the current flow to another flow. It enables you to modularize your conversation and organize it into separate flows.

The syntax for the engage statement in ChatFlow is as follows:

```
<engage_statement> ::= "engage" <flow_name>
```

In this syntax, the "flow_name" represents the name of the flow that you want to engage with. It allows you to initiate another flow within the current flow, continuing the conversation in a different context.

## Handover Statement

The handover statement in ChatFlow is used to transfer the conversation to another tributary, which is an user-defined external program. It allows you to hand over the conversation to a different system or service for further processing.

```
<handover_statement> ::= "handover" <tributary_name>
```

## End Statement

The end statement in ChatFlow is used to stop the execution of the entire program. It terminates the conversation and exits the ChatFlow program.

```
end_statement    ::= "end"
```

## Listen Statement

The listen statement in ChatFlow is used to listen for user input during the conversation. It allows the ChatFlow program to wait for the user to provide a response before continuing with the execution. If timeout is reached, the timeout variable in the context if automatically set.

```
<listen_statement> ::= "listen" "for" <variable> ("for" <time>)?
```

## Assign Statement

The assign statement in ChatFlow is used to assign a value to a variable. It allows you to store and manipulate data within the ChatFlow program.

```
<assign_statement> ::= "assign" <expression> "to" <variable>
```

## While Statement

The while statement in ChatFlow allows you to create a loop that executes a block of statements repeatedly as long as a specific condition is true.

```
<while_statement> ::= "while" <condition> "{" <block> "}"
```

## Store Statement

The store statement in ChatFlow is used to store a value in the parameter within the context, enabling the passing of information from one flow to another flow or a tributary. It allows you to store data that can be accessed and utilized across different parts of the conversation.

```
<store_statement> ::= "store" <value>
```

In this syntax, the "value" represents the data or value that you want to store in the parameter within the context. By utilizing the store statement, you can preserve and retrieve information as needed throughout the conversation. This feature facilitates seamless information sharing and enhances the flexibility and functionality of your ChatFlow program.

## Fetch Statement

The fetch statement in ChatFlow is used to retrieve the stored value from the parameter within the context. It allows you to access data that has been previously stored using the store statement.

```
<fetch_statement> ::= "fetch" <variable>
```

In this syntax, the "value" represents the data or value that you want to retrieve from the parameter within the context. By utilizing the fetch statement, you can access stored information and use it in your conversation flow. This enables you to leverage previously stored data and incorporate it into your ChatFlow program in a dynamic and customized manner.
