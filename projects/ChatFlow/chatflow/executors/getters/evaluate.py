from .property import *


def get_factor(factor, context):
    """Get the value of a factor.
    This function takes a factor and a context as input and returns the value of the factor.
    Args:
        factor (lark.Tree): The factor to evaluate.
        context (Context): The context in which the factor is evaluated.
    Returns:
        Any: The value of the factor.
    """
    factor = factor.children[0]
    if factor.data == "value":
        result = get_value(factor, context)
    else:
        result = get_expression(factor, context)
    return result


def get_term(term, context):
    """Get the value of a term.
    This function takes a term and a context as input and returns the value of the term.
    Args:
        term (lark.Tree): The term to evaluate.
        context (Context): The context in which the term is evaluated.
    Returns:
        Any: The value of the term.
    """
    factor = term.children[0]
    value = get_factor(factor, context)
    for i in range(1, len(term.children), 2):
        operator = term.children[i].children[0]
        factor = term.children[i + 1]
        factor_value = get_factor(factor, context)
        if operator.type == "TIMES":
            value *= factor_value
        elif operator.type == "DIVIDE":
            value /= factor_value
    return value


def get_expression(expression, context):
    """Get the value of an expression.
    This function takes an expression and a context as input and returns the value of the expression.
    Args:
        expression (lark.Tree): The expression to evaluate.
        context (Context): The context in which the expression is evaluated.
    Returns:
        Any: The value of the expression.
    """
    term = expression.children[0]
    value = get_term(term, context)
    for i in range(1, len(expression.children), 2):
        operator = expression.children[i].children[0]
        term = expression.children[i + 1]
        term_value = get_term(term, context)
        if operator.type == "PLUS":
            value += term_value
        elif operator.type == "MINUS":
            value -= term_value
    return value


def get_str_expression(expression, context):
    """Get the string representation of an expression.

    Args:
        expression (lark.Tree): The expression to evaluate.
        context (Context): The context in which the expression is evaluated.

    Returns:
        result (str): The string representation of the evaluated expression.
    """
    result = ""
    for child in expression.children:
        str_val = str(get_value(child, context))
        result += str_val
    return result
