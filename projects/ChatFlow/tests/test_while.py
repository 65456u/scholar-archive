from chatflow import run_stubbed_code


def test_while():
    expected_spoken = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
    user_input = []
    result = run_stubbed_code(user_input, expected_spoken, "test_while.flow")
    assert result
