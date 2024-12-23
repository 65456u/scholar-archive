tributary_dict = {}
"""
tributary_dict: A dictionary of tributary functions that can be used in ChatFlow.
"""


def register_tributary(tributary_name):
    """Register a tributary function to be used in ChatFlow

    Args:
        tributary_name (str): The name of the tributary to be registered

    Returns:
        function(callable): The decorated function

    """

    def decorator(func):
        tributary_dict[tributary_name] = func
        return func

    return decorator


def get_tributary(name: str):
    """Get a tributary function by name

    Args:
        name (str): The name of the tributary function to retrieve.

    Returns:
        function(callable): The tributary function corresponding to the given name.
    """
    return tributary_dict[name]
