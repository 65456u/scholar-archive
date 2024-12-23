from chatflow import register_tributary, run_stubbed_code


@register_tributary("test")
def tributary(context, speak_function, listen_function):
    speak_function("test")
    speak_function(context.get_parameter())


def test_handover():
    expected_spoken = ["test", "para"]
    user_input = []
    result = run_stubbed_code(user_input, expected_spoken, "test_handover.flow")
    assert result
