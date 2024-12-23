from chatflow import run_stubbed_code, register_tributary


def test_timeout():
    expected_spoken = ["Welcome to the recharge system", "timeout, please try again"]
    user_input = [None]
    result = run_stubbed_code(user_input, expected_spoken, "test_combined.flow")
    assert result


def test_recharge_timeout():
    expected_spoken = ["Welcome to the recharge system",
                       "please input the amount you want to recharge",
                       "timeout, please try again"]
    user_input = ["recharge", None]
    result = run_stubbed_code(user_input, expected_spoken, "test_combined.flow")
    assert result


@register_tributary("recharge")
def recharge(context, speak_function, listen_function):
    amount = context.get_parameter()
    print("recharging", amount, "yuan")
    print("recharge success")


@register_tributary("generate_random_number")
def generate_random_number(context, speak_function, listen_function):
    context.set_parameter(64)


def test_recharge():
    expected_spoken = ["Welcome to the recharge system",
                       "please input the amount you want to recharge",
                       ]
    user_input = ["recharge", "100"]
    result = run_stubbed_code(user_input, expected_spoken, "test_combined.flow")
    assert result


def test_query():
    expected_spoken = ["Welcome to the recharge system",
                       "Querying your balance", "You balance is 64 yuan"]
    user_input = ["query"]
    result = run_stubbed_code(user_input, expected_spoken, "test_combined.flow")
    assert result
