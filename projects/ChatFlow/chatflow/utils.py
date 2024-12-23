import asyncio
import inspect

import aioconsole
from inputimeout import inputimeout, TimeoutOccurred


def format_string(input_str: str, context):
    """Replace variables enclosed in curly braces with their corresponding values.

    Args:
        input_str (str): The input string containing variables to be replaced.
        context (Context): The context dictionary containing variable-value mappings.

    Returns:
        (str): The input string with variables replaced by their values.
    """
    start_index = input_str.find("{")
    end_index = input_str.find("}")

    while start_index != -1 and end_index != -1:
        if start_index > 0 and input_str[start_index - 1] == "\\":
            start_index = input_str.find("{", start_index + 1)
            end_index = input_str.find("}", end_index + 1)
            continue

        variable_name = input_str[start_index + 1: end_index]
        value = context.get_variable(variable_name)
        if value is not None:
            input_str = (
                    input_str[:start_index] + str(value) + input_str[end_index + 1:]
            )

        start_index = input_str.find("{", start_index + 1)
        end_index = input_str.find("}", end_index + 1)

    input_str = input_str.replace("\\{", "{").replace("\\}", "}")

    return input_str


async def timeout_checker(timeout):
    await asyncio.sleep(timeout)


async def a_read_input_with_timeout(timeout=None):
    """Reads input from the user with an optional timeout.

    Args:
        timeout (int, optional): The timeout value in seconds. Defaults to None.

    Returns:
        str: The input message from the user if received within the timeout, None otherwise.
    """
    if timeout is None:
        return input()
    else:
        timeout_task = asyncio.create_task(timeout_checker(timeout))
        input_task = asyncio.create_task(aioconsole.ainput())
        done, pending = await asyncio.wait(
            {timeout_task, input_task}, return_when=asyncio.FIRST_COMPLETED
        )

        if input_task in done:
            message = input_task.result()
            timeout_task.cancel()
            return message
        else:
            input_task.cancel()
            return None


def read_input_with_timeout(timeout=None):
    """Reads user input with an optional timeout.

    Args:
        timeout (float, optional): The timeout value in seconds. Defaults to None.

    Returns:
        str: The user input if received within the timeout, None otherwise.
    """
    try:
        if timeout is None:
            message = input()
        else:
            message = inputimeout(prompt="", timeout=timeout)
        return message
    except TimeoutOccurred:
        return None


async def aprint(*args, **kwargs):
    """Prints the given arguments to the console.

    Args:
        *args: The arguments to be printed.
        **kwargs: The keyword arguments to be printed.
    """
    print(*args, **kwargs, flush=True)


async def a_call_function(func, *args, **kwargs):
    """
    Calls a function, either synchronously or asynchronously, depending on the type of the function.

    Args:
        func (callable): The function to be called.
        *args: Positional arguments to be passed to the function.
        **kwargs: Keyword arguments to be passed to the function.

    Returns:
        The result of the function call.
    """
    if inspect.iscoroutinefunction(func):
        result = await func(*args, **kwargs)
    else:
        result = func(*args, **kwargs)

    return result


def call_function(func, *args, **kwargs):
    """Call a function and return the result.

    This function takes a function `func` as input along with any additional
    arguments and keyword arguments. It checks if the function is a coroutine
    function and runs it using asyncio if it is. Otherwise, it simply calls
    the function and returns the result.

    Args:
        func (callable): The function to be called.
        *args: Additional positional arguments to be passed to the function.
        **kwargs: Additional keyword arguments to be passed to the function.

    Returns:
        Any: The result of calling the function.

    """
    if inspect.iscoroutinefunction(func):
        result = asyncio.run(func(*args, **kwargs))
    else:
        result = func(*args, **kwargs)
    return result
