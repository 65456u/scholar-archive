## Installation

### ~~Install using PyPI~~

You can install ChatFlow from PyPI using the following command:

```shell
pip install chatflow
```

### Install from source

Alternatively, you can install it from the source code. First, clone the repository:

```shell
git clone https://github.com/65456u/ChatFlow.git
cd ChatFlow
```

Then, install the required packages:

```shell
pip install -r requirements.txt
```

Finally, install ChatFlow:

```shell
pip install .
```

## Initializing the Interpreter

To run a ChatFlow program, you need to create an `Interpreter` object using the ChatFlow code you have written.

You can directly create an `Interpreter` object and pass the code as a string, like this:

```python
from chatflow import Interpreter

code = """
flow origin {
  speak "Hello, world!" 
}
"""

interpreter = Interpreter(code=code)
```

Alternatively, you can create an `Interpreter` object by specifying the path to a file containing your ChatFlow code:

```python
interpreter = Interpreter(code_path="hello.flow")
```

## Creating a Runtime Instance

The `Runtime` class is responsible for executing the ChatFlow program.

You can create a `Runtime` instance by passing the `Interpreter` object along with your custom `speak` and `listen` functions. If you don't provide custom functions, the runtime will use the built-in default `speak` and `listen` methods.

```python
from chatflow import Interpreter, Runtime


def my_speak_function(message):
# Custom speak function implementation
# ...

def my_listen_function(timer):
# Custom listen function implementation
# ...


runtime = Runtime(interpreter, my_speak_function, my_listen_function)
```

By providing your own `speak` and `listen` functions, you can customize the behavior of the ChatFlow program according to your needs.

## Running the Program

To execute the ChatFlow program, simply call the `run()` method on the `Runtime` instance:

```python
runtime.run()
```

This will start the execution of the ChatFlow program, which will proceed according to the defined flows and interactions specified in the code.
