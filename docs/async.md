**Async Support**
=================

ChatFlow supports async mode in Python out of the box. To enable asynchronous execution of ChatFlow programs, you just need to use `Runtime.arun()` instead of `Runtime.run()`. 

For example, the following synchronous program:

    def main():
        interpreter = Interpreter(code=code)
        runtime = Runtime(interpreter)
        runtime.run()
       
    if __name__ == "__main__":
        main()

can be easily tranformed into asynchronous mode:

    async def main():
        interpreter = Interpreter(code=code) 
        runtime = Runtime(interpreter, async_flag=True)
        await runtime.arun()
    
    if __name__ == "__main__":
        asyncio.run(main())

You can also define your custom async speak and listen functions as well as async tributaries.

In summary, ChatFlow enables:

- Async mode with simple Runtime swap
- Custom async speak, listen and tributaries
- Asynchronous, non-blocking execution
