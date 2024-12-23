import pytest

from chatflow import Interpreter, Runtime, create_stubbed_functions, run_stubbed_code


def test_scope():
    expected_spoken = []
    user_input = []
    with pytest.raises(NameError):
        run_stubbed_code(user_input, expected_spoken, "test_scope.flow")
