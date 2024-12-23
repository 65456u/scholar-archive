from chatflow import run_stubbed_code


def test_engage():
    expected_spoken = ["engaged"]
    user_input = []
    result = run_stubbed_code(user_input, expected_spoken, "test_engage.flow")
    assert result
