# Examples

Following are some example scripts of ChatFlow and their explanations:

## Count to Ten

```
flow origin {
    assign 0 to count
    while count less than 10 {
        assign count + 1 to count
        speak count
    }
}
```



When the "origin" flow starts:

1. A variable `count` is initialized to 0

2. A `while` loop begins which will iterate as long as `count` is less than 10

3. In each iteration:

    a) `count` is incremented by 1 
    
    b) The current value of `count` is spoken out loud
    
    c) This continues till `count` reaches 10

So the core behavior would be:

- Initialize count variable 
- Enter while loop
- Increment counter per iteration
- Speak updated count per loop
- Loop till termination condition is false

So effectively, this would speak the numbers from 1 through 10 sequentially, demonstrating use of variables, conditional loops, variable assignments, and speak statements in ChatFlow.

Let me know if you need any clarification or have additional questions on this example!

## Guess Number Game

```
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
```

When this script is executed, the interpreter would behave as follows:

1. The "origin" flow begins execution. It first speaks prompting the user to guess a number.

2. The "generate_random_number" tributary is handed over control to generate a random number between 1-100 and store it in the context.

3. The number in the parameter of the Context is stored into number by `fetch number`

4. A while loop begins which iterates until the user guesses the correct number.

5. In each iteration, the user's input is listened to, stored into parameter, processed by `string_to_number`  tributary, re-stored into num, and validated as a number.

6. The input is converted to an integer and compared against the randomly generated number:

   a. If too small/large, corresponding hints are provided.

   b. If correct, a success message is spoken and execution ends.

7. If invalid input, an error message is spoken.

## Recharge Service

```
flow origin {
    speak "Welcome to the recharge system"
    listen for question for 10s
    if timeout {
        engage timeout_flow
    }
    if question matches "recharge" {
        engage recharge_flow
    } else if question matches "query" {
        engage query_flow
    } else {
        engage unknown_flow
    }
}

flow timeout_flow {
    speak "timeout, please try again"
    end
}

flow recharge_flow {
    speak "please input the amount you want to recharge"
    listen for question for 10s
    if timeout {
        engage timeout_flow
    }
    if question matches "\d+" as amount {
        store amount
        handover recharge
        end
    }
    engage unknown_flow
}

flow unknown_flow {
    speak "Sorry, I don't understand what you are saying"
    end
}

flow query_flow {
    speak "Querying your balance"
    handover query_balance
    end
}
```

When the "origin" flow starts, the user is welcomed and prompted to ask a question. The program listens for 10 seconds to get the user's input.

There are several possible paths:

1. If timeout occurs, the "timeout_flow" is engaged which speaks a timeout message and exits.
2. If the input matches "recharge", the "recharge_flow" is initiated. It asks for recharge amount, listens for input, validates it as a number, stores it, and hands over to the "recharge" tributary to handle the actual recharge.
3. If the input matches "query", the "query_flow" is started which directly hands over control to the "query_balance" tributary to query & display account balance before exiting.
4. For any other input, the "unknown_flow" is engaged, which speaks an error message before exiting.