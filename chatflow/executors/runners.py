"""
Executors for running different types of statements.
"""

from .setters import *
from ..tributary import get_tributary
from ..utils import a_call_function, call_function


async def arun_handover(statement, context, speak_function, listen_function):
    """
    Executes a handover to a specific tributary.

    Args:
        statement (lark.Tree): The statement object.
        context (Context): The context object.
        speak_function (callable): The function used for speaking.
        listen_function (callable): The function used for listening.

    Raises:
        Exception: If the specified tributary is not found.
    """
    tributary_name = get_tributary_name(statement.children[0])
    tributary = get_tributary(tributary_name)
    if tributary is None:
        raise Exception(f"Tributary {tributary_name} not found")
    await a_call_function(tributary, context, speak_function, listen_function)


def run_handover(statement, context, speak_function, listen_function):
    """
    Executes a handover to a specific tributary.

    Args:
        statement (lark.Tree): The statement object.
        context (Context): The context object.
        speak_function (callable): The function used for speaking.
        listen_function (callable): The function used for listening.

    Raises:
        Exception: If the specified tributary is not found.
    """
    tributary_name = get_tributary_name(statement.children[0])
    tributary = get_tributary(tributary_name)
    if tributary is None:
        raise Exception(f"Tributary {tributary_name} not found")
    call_function(tributary, context, speak_function, listen_function)


def run_assign(statement, context):
    """Assigns a value to a variable in the given context.

    Args:
        statement (lark.Tree): The assignment statement to be executed.
        context (Context): The context in which the assignment is performed.
    """
    expression = statement.children[0]
    value = get_expression(expression, context)
    variable = statement.children[1]
    variable_name = get_variable_name(variable)
    context.set_variable(variable_name, value)


async def arun_speak(statement, context, speak_function):
    """Executes the speak function with the value obtained from the statement.

    Args:
        statement (lark.Tree): The statement from which to obtain the value.
        context (Context): The context in which the statement is evaluated.
        speak_function (callable): The function to be executed with the obtained value.
    """
    value = get_str_expression(statement.children[0], context)
    await a_call_function(speak_function, value)


def run_speak(statement, context, speak_function):
    """Executes the speak function with the value obtained from the statement.

    Args:
        statement (lark.Tree): The statement from which to obtain the value.
        context (Context): The context in which the statement is evaluated.
        speak_function (callable): The function to be executed with the obtained value.
    """
    value = get_str_expression(statement.children[0], context)
    call_function(speak_function, value)


async def arun_listen(statement, context, listen_function):
    """Executes the listen statement.

    Args:
        statement (lark.Tree): The listen statement node.
        context (Context): The execution context.
        listen_function (callable): The function to be called for listening.

    Returns:
        (int): The value obtained from the listen function. None if timeout occurs.
    """
    length = len(statement.children)
    match length:
        case 1:
            value = await a_call_function(listen_function)
            set_variable(statement.children[0], context, value)
        case 2:
            timer = get_time(statement.children[1], context)
            value = await a_call_function(listen_function, timer)
            if value is None:
                context.set_timeout(True)
            else:
                set_variable(statement.children[0], context, value)


def run_listen(statement, context, listen_function):
    """Executes the listen statement.

    Args:
        statement (lark.Tree): The listen statement node.
        context (Context): The execution context.
        listen_function (callable): The function to be called for listening.

    Returns:
        (int): The value obtained from the listen function. None if timeout occurs.
    """
    length = len(statement.children)
    match length:
        case 1:
            value = call_function(listen_function)
            set_variable(statement.children[0], context, value)
        case 2:
            timer = get_time(statement.children[1], context)
            value = call_function(listen_function, timer)
            if value is None:
                context.set_timeout(True)
            else:
                set_variable(statement.children[0], context, value)


def run_store(statement, context):
    """Executes the store statement.

    Args:
        statement (lark.Tree): The store statement node.
        context (Context): The execution context.
    """
    value = get_value(statement.children[0], context)
    context.set_parameter(value)


def run_fetch(statement, context):
    """Executes the fetch statement.

    Args:
        statement (lark.Tree): The fetch statement node.
        context (Context): The execution context.
    """
    value = context.get_parameter()
    set_variable(statement.children[0], context, value)
