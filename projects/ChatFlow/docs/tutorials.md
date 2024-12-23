# Learning ChatFlow

## The First ChatFlow Program

Let's write our first ChatFlow program that says "hello" to the world.

```chatflow
flow origin {
  speak "Hello, world!" 
}
```

To run this program, you can use the following Python code:

```python
from chatflow import Interpreter, Runtime

code = """
flow origin {
  speak "Hello, world!" 
}
"""

interpreter = Interpreter(code=code)
runtime = Runtime(interpreter)
runtime.run() 
```

The current program only has one flow called "origin," which serves as the entry point of the entire ChatFlow program.

We first create an `Interpreter` object using the provided code. Then we use the `Interpreter` to create a `Runtime` object. After that, we can execute the program by calling `runtime.run()`.

So far, we have only passed the code to the ChatFlow. However, soon we will learn how to define our own `speak` and `listen` functions, as well as implement our own tributary.

## A Parrot

Our second ChatFlow program will be a parrot that simply echoes the user's input.

```chatflow
flow origin {
	listen for message
	speak message
}
```

In our parrot program, we store the user input in the variable `message` and then speak it back to the user.

But what if we want the parrot to continue listening and echoing until we tell it to stop? We can modify the code like this:

```chatflow
flow origin {
	while true {
		listen for message
		speak message
	}
}
```

If we want the parrot to echo a specific number of times, we can alter the code like this:

```chatflow
flow origin {
	variable counter = 0
	while counter < 5 {
		listen for message
		speak message
		counter = counter + 1
	}
}
```

In this modified version, we introduce a variable called `counter` and initialize it to 0. Inside the loop, we listen for a message, speak it, and then increment the counter. The loop continues until the counter reaches 5.

These examples demonstrate how you can use ChatFlow to create simple conversational programs. As you learn more about ChatFlow, you'll be able to define more complex behaviors and interactions.

## Listen

The `listen` command in ChatFlow allows the program to wait for user input and store it in a variable for further processing. It is a crucial component for creating interactive conversational experiences.

The basic usage of `listen` involves specifying the type of input to listen for and the variable to store the received input. Here's an example:

```chatflow
flow origin {
    listen for message
    speak message
}
```

In this example, the program listens for a `message` from the user. Once the user provides a message, it is stored in the `message` variable, and the program responds by speaking the same message back to the user. This simple pattern allows the program to act as a parrot, echoing the user's input.

In some scenarios, it may not be desirable to indefinitely listen for user input. For instance, you may want to set a time limit for how long the program waits for input. In such cases, you can use the optional `for` parameter to specify a timeout duration.

```chatflow
flow origin {
    listen for message for 5s
    if timeout {
        speak "Timeout occurred."
    } else {
        speak message
    }
}
```

In this modified example, the program listens for a `message` for a maximum duration of 5 seconds. If no input is received within the specified time, the `timeout` condition is triggered. Inside the `if timeout` block, the program speaks "Timeout occurred." If input is received within the time limit, the program proceeds to speak the stored message.

By incorporating the `listen` command with or without a timeout, you can create interactive conversational flows that respond to user input in real-time.

## Speak

The `speak` command in ChatFlow is a fundamental component for generating responses and providing information to the user in a conversational manner. It allows the program to communicate with the user by speaking out messages.

Using the `speak` command is straightforward. Simply provide the content you want the program to speak within quotation marks. Here are a few examples:

### Literal Content
```chatflow
flow origin {
    speak "Hello, world!"
}
```
In this example, the program speaks the literal content "Hello, world!" to the user.

### Variable Content
```chatflow
flow origin {
    assign "123456" to content
    speak content
}
```
This example demonstrates how you can assign a value, such as "123456", to a variable called `content`. The program then speaks the value stored in the `content` variable.

### Dynamic Content
```chatflow
flow origin {
    speak "What's your name?"
    listen for name
    speak "Hello, " + name + "!"
}
```
In this example, the program first speaks the question "What's your name?". It then listens for the user's input, storing it in the `name` variable. Finally, it constructs a dynamic message by combining the stored `name` with other strings and speaks the personalized greeting.

By utilizing the `speak` command in different ways, you can create engaging and interactive conversations with your program. Whether it's providing static messages, speaking variable content, or dynamically generating responses, the `speak` command allows for effective communication in a customer service chatbot.

## Define Custom Speak and Listen Functions

In ChatFlow, you have the flexibility to define your own `speak` and `listen` functions to customize the behavior of your program. 

A `speak` function takes a single parameter, which is the content it will speak. It does not require a return value. You can define your own `speak` function to add additional functionality, such as printing the number of times you speak along with the content. Here's an example:

```python
def create_my_speak(initial=0):
    def my_speak_function(message):
        nonlocal initial
        initial += 1
        print(initial, message)

    return my_speak_function

def main():
    interpreter = Interpreter(code=code)
    runtime = Runtime(interpreter, speak_function=create_my_speak())
    runtime.run()
```

In this example, we define a `create_my_speak` function that returns a customized `speak` function. The `create_my_speak` function takes an optional initial value parameter and defines the `my_speak_function` nested function. The `my_speak_function` increments the `initial` value and prints the incremented value along with the message content.

A `listen` function receives a timer value, which specifies the maximum time to wait for user input in second. If the `timeout` parameter is None, it means that no timeout is required, and the program will listen for customer input indefinitely. The `listen` function returns the content it hears, or `None` if a timeout occurs. 

The built-in `listen` function is implemented as follows:

```python
def read_input_with_timeout(timeout=None):
    try:
        if timeout is None:
            message = input()
        else:
            message = inputimeout(prompt='', timeout=timeout)
        return message
    except TimeoutOccurred:
        return None
```

This function uses the `input` function from Python's standard library to read user input. If a `timeout` value is provided, it uses the `inputimeout` function to limit the waiting time for input. If a timeout occurs, the function returns `None`.

By defining custom `speak` and `listen` functions, you can extend the capabilities of your ChatFlow programs and tailor them to your specific requirements.

## Flow Control

When executing a ChatFlow program, it can be visualized as traversing through different flows. Each flow represents a distinct sequence of actions and interactions within the program. As the execution progresses, the program moves from one flow to another based on the logic and control flow defined in the code.

Think of the flows as different destinations or checkpoints in your program. The program starts at the flow origin, which serves as the starting point. From there, it engages other flows using the `engage` statement to navigate to different sections of the program.

As the program traverses through flows, it executes the code within each flow, performing the defined actions and interacting with the user or external systems as necessary. The program may move back and forth between different flows, depending on the logic and conditions specified in the code.

The flow-based execution model allows you to structure your program's conversations and actions in a modular and organized manner. By breaking down your program into flows, you can isolate different functionalities and make your code more manageable and maintainable.

The flow origin serves as the entry point of the entire program. It is where the execution starts. From the flow origin, you can navigate to other flows using the `engage` statement.

For example:
```chatflow
flow origin {
	while true {
		engage echo
	}
}

flow echo {
	listen for message
	speak message
}
```

In this example, the flow origin is defined as a loop that runs indefinitely (`while true`). Within the loop, the `engage` statement is used to step into another flow called "echo". This means that the program will leave the current flow and start executing the code in the "echo" flow. Once the code in the "echo" flow is completed, the program will return to the flow origin and continue with the next iteration of the loop.

The "echo" flow listens for a message and then speaks the received message back to the user. It represents a specific sequence of actions that are separate from the flow origin.

By using flows and the `engage` statement, you can create more complex conversational programs with different paths and interactions. Each flow can have its own set of actions, conditions, and responses. This allows you to structure your program in a modular and organized way, making it easier to understand and maintain.

## Creating a Tributary

In ChatFlow, you can create a tributary to extend the functionality of your conversational programs. Tributaries are external functions that can be seamlessly integrated into your ChatFlow program to perform custom operations. Let's explore an example of creating and utilizing a tributary called "parameter_printer":

To create the tributary, you need to define a flow that engages it. Here's an example flow that utilizes the "parameter_printer" tributary:

```chatflow
flow origin {
    listen for message
    store message
    handover parameter_printer
}
```

In this example, the flow origin listens for a message from the user and stores it in the conversation's context. Then, it engages the "parameter_printer" tributary using the `handover` statement.

Now let's define the "parameter_printer" tributary function in Python:

```python
@register_tributary("parameter_printer")
def parameter_printer(context, speak_function, listen_function):
    para = context.get_parameter()
    speak_function(para)
```

In this code snippet, the "parameter_printer" function is registered as a tributary using the `@register_tributary` decorator. The function takes three parameters: `context`, `speak_function`, and `listen_function`. The `context` parameter provides access to the conversation's context, allowing you to retrieve stored data. The `speak_function` parameter represents the function used to speak or output content to the user.

In the "parameter_printer" function, the `context.get_parameter()` retrieves the stored message from the conversation's context. Then, the `speak_function(para)` outputs the retrieved message to the user.

By creating this tributary and engaging it within the flow, you can seamlessly incorporate the custom functionality of the "parameter_printer" tributary into your conversational program.

Tributaries in ChatFlow enable you to extend the capabilities of your chatbot or conversational agent by integrating custom logic and actions. They provide a flexible and modular approach to enhance the functionality and interactivity of your conversational programs.

## Branch

Branch control is a crucial aspect of building conversational programs in ChatFlow. It allows the program to make decisions and take different paths based on specific conditions. By using branching statements, you can create more interactive and dynamic chatbot experiences.

To best fit the needs of a chatbot, ChatFlow provides several branching mechanisms. Let's explore some of them:

### Matching Variable Content
The `match` statement is used to compare if a variable matches a specific regular expression pattern. It allows you to perform pattern matching and conditionally execute code based on the result.

```chatflow
flow origin {
    listen for question for 5s
    if timeout {
        speak "Timeout, conversation ended."
    } else if question match "(top up|recharge)" {
        engage charge_flow
    } else {
        speak "Unrecognized request."
        end
    }
}
```

In this example, the program listens for a `question` for a maximum of 5 seconds. If a timeout occurs, it speaks "Timeout, conversation ended." If the `question` matches the regular expression pattern `(top up|recharge)`, it engages the `charge_flow` flow. Otherwise, it speaks "Unrecognized request" and ends the conversation.

### Equality Comparison
The `equals` statement is used to check if two values are equal. It is often used for comparing user input against expected values.

```chatflow
flow confirm {
    speak "Do you really want to charge " + n + " yuan? Please answer with 'yes' to proceed or 'no' to cancel."
    assign false to confirmed
    while not confirmed {
        listen for confirmation
        if confirmation equals "yes" {
            handover charge_tributary
            assign true to confirmed
        } else if confirmation equals "no" {
            speak "Charge cancelled."
            end
        } else {
            speak "Please answer with 'yes' or 'no' only. Please repeat your choice."
        }
    }
}
```

In this example, the program asks the user if they want to charge a specific amount. It listens for a `confirmation` and uses the `equals` statement to compare the input against "yes" and "no". If the confirmation is "yes", it hands over to the `charge_tributary` flow and sets `confirmed` to `true`. If the confirmation is "no", it speaks "Charge cancelled" and ends the conversation. If the confirmation is neither "yes" nor "no", it speaks a reminder message and continues listening for a valid response.

### Timeout Handling
ChatFlow provides a built-in variable called `timeout` that is automatically set after a `listen` statement. It allows you to handle timeouts and take appropriate actions when no input is received within a specified duration.

```chatflow
flow origin {
    listen for question for 5s
    if timeout {
        speak "Timeout, conversation ended."
    } else {
        // Handle user input
    }
}
```

In this example, the program listens for a `question` for a maximum of 5 seconds. If no input is received within the specified time, the `timeout` condition is triggered. Inside the `if timeout` block, the program speaks "Timeout, conversation ended." You can use this mechanism to gracefully handle situations where the user takes too long to respond.

By utilizing branching statements like `match`, `equals`, and `timeout`, you can create more sophisticated conversational flows in ChatFlow. These branching mechanisms enable your chatbot to make decisions based on user input and provide appropriate responses, enhancing the interactive and dynamic nature of the conversation.
