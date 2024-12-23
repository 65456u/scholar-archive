import re

from .evaluate import *
from .property import *


def get_match_compare(condition, context):
    """Get the match compare result.

    This function takes a condition and a context as input and performs a match compare operation.
    It checks if the expression matches the value using regular expressions.

    Args:
        condition (lark.Tree): The condition object containing the expression, value, and optional variable.
        context (Context): The context object containing the variables.

    Raises:
        Exception: If the expression or value is not a string.

    Returns:
        result (bool): True if the expression matches the value, False otherwise.
    """
    expression = condition.children[0]
    expression = get_expression(expression, context)
    value = condition.children[1]
    value = get_value(value, context)
    if type(expression) is not str or type(value) is not str:
        raise Exception("Match compare only supports string values")
    if len(condition.children) == 2:
        return re.match(value, expression)
    else:
        variable = condition.children[2]
        variable = get_variable_name(variable)
        result = re.search(value, expression)
        if result:
            context.set_variable(variable, result.group())
            return True
        else:
            context.set_variable(variable, None)
            return False


def get_larger_compare(condition, context):
    """Get the larger compare result.

    Args:
        condition (lark.Tree): the condition object
        context (Context): the context object
    Returns:
        bool: the result of the compare
    """
    first_expression = condition.children[0]
    second_expression = condition.children[1]
    first_value = get_expression(first_expression, context)
    second_value = get_expression(second_expression, context)
    return first_value > second_value


def get_less_compare(condition, context):
    """
    Compare two values and return True if the first value is less than the second value.

    Args:
        condition (Expression): The condition to evaluate.
        context (Context): The context in which the condition is evaluated.

    Returns:
        result (bool): True if the first value is less than the second value, False otherwise.
    """
    first_expression = condition.children[0]
    second_expression = condition.children[1]
    first_value = get_expression(first_expression, context)
    second_value = get_expression(second_expression, context)
    return first_value < second_value


def get_condition(condition, context):
    """
    Get the value of a condition based on its type.

    Args:
        condition (lark.Tree): The condition node.
        context (Context): The context dictionary.

    Returns:
        result (bool): The value of the condition.

    """
    condition = condition.children[0]
    condition_type = condition.data
    match condition_type:
        case "match_compare":
            return get_match_compare(condition, context)
        case "equal_compare":
            return get_equal_compare(condition, context)
        case "larger_compare":
            return get_larger_compare(condition, context)
        case "less_compare":
            return get_less_compare(condition, context)
        case "timeout":
            return context.timeout
        case "boolean":
            return get_boolean(condition)
        case "condition":
            return not get_condition(condition, context)


def get_equal_compare(condition, context):
    """Get the equal compare result.

    Args:
        condition (lark.Tree): The condition to be compared.
        context (Context): The context in which the comparison is performed.

    Returns:
        result (bool): True if the first value is equal to the second value, False otherwise.
    """
    first_expression = condition.children[0]
    second_expression = condition.children[1]
    first_value = get_expression(first_expression, context)
    second_value = get_expression(second_expression, context)
    return first_value == second_value
