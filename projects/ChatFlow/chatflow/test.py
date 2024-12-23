from . import Interpreter, Runtime


def create_stubbed_functions(input_list: list, output_list: list):
    """Creates a stub for the speak and listen functions.

    Args:
        input_list (list): A list of strings to be returned by the listen function.
        output_list (list): A list of strings to be compared with the spoken list.

    Returns:
        (tuple): A tuple containing the stubbed speak and listen functions.
    """
    spoken = []

    def speak_function(message):
        nonlocal spoken
        spoken.append(message)

    def listen_function(timeout=None):
        nonlocal input_list
        if len(input_list) == 0:
            return None
        else:
            return input_list.pop(0)

    def judge():
        nonlocal spoken
        nonlocal output_list
        return spoken == output_list

    return speak_function, listen_function, judge


def run_stubbed_code(input_list: list, output_list: list, code_path: str):
    """Runs the code with stubbed speak and listen functions.

    Args:
        input_list (list): A list of strings to be returned by the listen function.
        output_list (list): A list of strings to be compared with the spoken list.
        code_path (str): The path to the code file.

    Returns:
        (bool): True if the spoken list matches the output list, False otherwise.
    """
    speak, listen, judge = create_stubbed_functions(input_list, output_list)
    interpreter = Interpreter(code_path=code_path)
    runtime = Runtime(interpreter, speak, listen)
    runtime.run()
    return judge()
