def get_literal(tree):
    """
    Get the literal value from the parse tree.
    Args:
        tree (lark.Tree): The parse tree node representing the literal value.
    Returns:
        Any: The literal value.
    """
    value = tree.children[0]
    match value.type:
        case "STRING_LITERAL":
            value = value.value[1:-1]
        case "NUMBER_LITERAL":
            value = int(value.value)
    return value


def get_variable(value, context):
    """
    Get the value of a variable from the context.
    Args:
        value (lark.Tree): The parse tree node representing the variable.
        context (Context): The context object containing variable values.
    Returns:
        Any: The value of the variable.
    """
    variable_name = value.children[0].value
    return context.get_variable(variable_name)


def get_value(tree, context):
    """
    Get the value from the parse tree.
    Args:
        tree (lark.Tree): The parse tree node representing the value.
        context (Context): The context object containing variable values.
    Returns:
        Any: The value.
    """
    value = tree.children[0]
    match value.data:
        case "literal":
            return get_literal(value)
        case "variable":
            variable_name = get_variable_name(value)
            return context.get_variable(variable_name)


def get_identifier(tree):
    """
    Get the identifier value from the parse tree.
    Args:
        tree (lark.Tree): The parse tree node representing the identifier.
    Returns:
        Any: The identifier value.
    """
    return tree.children[0].value


def get_variable_name(tree) -> str:
    """
    Get the variable name from the parse tree.
    Args:
        tree (lark.Tree): The parse tree node representing the variable.
    Returns:
        (str): The variable name.
    """
    return get_identifier(tree.children[0])


def get_time(tree, context) -> int:
    """
    Get the time value from the parse tree.
    Args:
        tree (lark.Tree): The parse tree node representing the time value.
        context (Context): The context object containing variable values.
    Returns:
        int: The time value in seconds.
    """
    timer = tree.children[0]
    timer = get_value(timer, context)
    unit = tree.children[1].children[0].data
    match unit:
        case "second":
            timer *= 1
        case "minute":
            timer *= 60
        case "hour":
            timer *= 3600
    return timer


def get_flow_name(tree) -> str:
    """
    Get the flow name from the parse tree.
    Args:
        tree (lark.Tree): The parse tree node representing the flow name.
    Returns:
        str: The flow name.
    """
    name = get_identifier(tree.children[0])
    return name


def get_tributary_name(tree) -> str:
    """
    Get the tributary name from the parse tree.
    Args:
        tree (lark.Tree): The parse tree node representing the tributary name.
    Returns:
        str: The tributary name.
    """
    name = get_identifier(tree.children[0])
    return name


def get_boolean(condition):
    """
    Get the boolean value from the parse tree.
    Args:
        condition (lark.Tree): The parse tree node representing the boolean value.
    Returns:
        bool: The boolean value.
    Raises:
        Exception: If the boolean value is unknown.
    """
    condition = condition.children[0]
    if condition.type == "TRUE":
        return True
    elif condition.type == "FALSE":
        return False
    else:
        raise Exception("Unknown boolean")
