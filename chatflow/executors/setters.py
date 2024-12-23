from .getters import *


def set_variable(tree, context, value):
    """Set the value of a variable in the context.

    Args:
        tree (lark.Tree): The tree object.
        context (Context): The context object.
        value (any): The value to set.

    """
    variable_name = get_variable_name(tree)
    context.set_variable(variable_name, value)
