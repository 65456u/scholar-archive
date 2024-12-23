from chatflow import run_stubbed_code


def test_if():
    expected_spoken = ["start"]
    user_input = ["start"]
    result = run_stubbed_code(user_input, expected_spoken, "test_branch.flow")
    assert result


def test_elif():
    expected_spoken = ["final"]
    user_input = ["final"]
    result = run_stubbed_code(user_input, expected_spoken, "test_branch.flow")
    assert result


def test_else():
    expected_spoken = ["default"]
    user_input = ["default"]
    result = run_stubbed_code(user_input, expected_spoken, "test_branch.flow")
    assert result
