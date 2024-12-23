import random

from chatflow import Interpreter, register_tributary, Runtime


@register_tributary("generate_random_number")
def generate_random_number(context, speak_function, listen_function):
    number = random.randint(1, 100)
    context.set_parameter(number)


@register_tributary("string_to_number")
def s2n(context, speak_function, listen_function):
    number = int(context.get_parameter())
    context.set_parameter(number)


code = r"""
flow origin {
    speak "guess a number between 1 and 100"
    handover generate_random_number
    fetch number
    while true {
        listen for answer
        if answer matches "\d+" as num {
            store num
            handover string_to_number
            fetch num
            if num larger than number {
                speak "too large"
            } else if num less than number {
                speak "too small"
            } else {
                speak "correct"
                end
            }
        } else {
            speak "not even wrong"
        }
    }
}
"""


def create_my_speak(initial=0):
    def my_speak_function(message):
        nonlocal initial
        initial += 1
        print(initial, message)

    return my_speak_function


def main():
    interpreter = Interpreter(code=code)
    runtime = Runtime(interpreter)
    runtime.run()


if __name__ == "__main__":
    main()
