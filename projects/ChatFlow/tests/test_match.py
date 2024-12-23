from chatflow import run_stubbed_code


def test_match():
    expected_spoken = ["6633"]
    user_input = ["6633人"]
    result = run_stubbed_code(user_input, expected_spoken, "test_match.flow")
    assert result
