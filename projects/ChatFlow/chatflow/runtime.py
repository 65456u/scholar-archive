from .context import Context
from .executors import *
from .utils import *


class Runtime:
    """
    The Runtime class represents the execution environment for the ChatFlow program.

    Attributes:
        tree (lark.Tree): The abstract syntax tree of the ChatFlow program.
        flow_dict (dict): A dictionary mapping flow names to their corresponding blocks.
        exit (bool): A flag indicating whether the chat flow should exit.
        contextStack (list): A stack of context objects representing the execution context.
        speak_function (callable): The function used for speaking.
        listen_function (callable): The function used for listening.

    Methods:
        __init__(self, interpreter, speak_function=None, listen_function=None): Initializes the Runtime object.
        register_flow(self): Registers the flows defined in the ChatFlow program.
        run(self): Runs the chat flow.
        arun(self): Runs the chat flow asynchronously.
        arun_flow(self, flow_name, parameter=None): Runs a specific flow in the ChatFlow program asynchronously.
        run_flow(self, flow_name, parameter=None): Runs a specific flow in the ChatFlow program.
        arun_block(self, block, context): Runs a block of statements in the ChatFlow program asynchronously.
        run_block(self, block, context): Runs a block of statements in the ChatFlow program.
        run_statement(self, statement, context): Runs a single statement in the ChatFlow program.
        arun_statement(self, statement, context): Runs a single statement in the ChatFlow program asynchronously.
        arun_if(self, statement, context): Runs an if statement in the ChatFlow program asynchronously.
        run_if(self, statement, context): Runs an if statement in the ChatFlow program.
        arun_else(self, statement, context): Runs an else statement in the ChatFlow program asynchronously.
        run_else(self, statement, context): Runs an else statement in the ChatFlow program.
        arun_engage(self, statement, context): Runs an engage statement in the ChatFlow program asynchronously.
        run_engage(self, statement, context): Runs an engage statement in the ChatFlow program.
        arun_while(self, statement, context): Runs a while statement in the ChatFlow program asynchronously.
        run_while(self, statement, context): Runs a while statement in the ChatFlow program.
    """

    def __init__(self, interpreter, speak_function=None, listen_function=None):
        """Initialize the Runtime object.

        Args:
            interpreter (Interpreter): The interpreter object.
            speak_function (callable, optional): The function used for speaking. Defaults to print.
            listen_function (callable, optional): The function used for listening. Defaults to read_input_with_timeout.

        """
        self.tree = interpreter.tree
        self.flow_dict = {}
        self.exit = False
        self.register_flow()
        self.contextStack = []
        self.speak_function = speak_function
        self.listen_function = listen_function

    def register_flow(self):
        """
        Register the flows defined in the ChatFlow program.
        """
        for flow in self.tree.children:
            flow_name = flow.children[0].children[0].children[0]
            block = flow.children[1]
            self.flow_dict[flow_name] = block

    def run(self):
        """
        Runs the chat flow.

        If the speak_function is not provided, it defaults to the print function.
        If the listen_function is not provided, it defaults to the read_input_with_timeout function.

        The chat flow starts from the "origin" flow.
        """
        if self.speak_function is None:
            self.speak_function = print
        if self.listen_function is None:
            self.listen_function = read_input_with_timeout
        self.run_flow("origin")

    async def arun(self):
        """Runs the chatflow asynchronously.

        This method is responsible for executing the chatflow asynchronously.
        It sets the default speak and listen functions if not provided,
        and then calls the `arun_flow` method to start the chatflow.

        """
        if self.speak_function is None:
            self.speak_function = aprint
        if self.listen_function is None:
            self.listen_function = a_read_input_with_timeout
        await self.arun_flow("origin")

    async def arun_flow(self, flow_name, parameter=None):
        """
        Run a specific flow in the ChatFlow program.

        Args:
            flow_name (str): The name of the flow to run.
            parameter (any, optional): The parameter to pass to the flow. Defaults to None.
        """
        if flow_name not in self.flow_dict:
            raise Exception(f"Flow {flow_name} not found")
        tree = self.flow_dict[flow_name]
        context = Context(parameter, tree)
        self.contextStack.append(context)
        await self.arun_block(tree, context)
        self.contextStack.pop()

    def run_flow(self, flow_name, parameter=None):
        """
        Run a specific flow in the ChatFlow program.

        Args:
            flow_name (str): The name of the flow to run.
            parameter (any, optional): The parameter to pass to the flow. Defaults to None.
        """
        if flow_name not in self.flow_dict:
            raise Exception(f"Flow {flow_name} not found")
        tree = self.flow_dict[flow_name]
        context = Context(parameter, tree)
        self.contextStack.append(context)
        self.run_block(tree, context)
        self.contextStack.pop()

    async def arun_block(self, block, context):
        """
        Run a block of statements in the ChatFlow program.

        Args:
            block (lark.Tree): The block of statements to run.
            context (Context): The current context.
        """
        context.push_scope()
        for statement in block.children:
            if self.exit:
                return
            await self.arun_statement(statement, context)

    def run_block(self, block, context):
        """
        Run a block of statements in the ChatFlow program.

        Args:
            block (lark.Tree): The block of statements to run.
            context (Context): The current context.
        """
        context.push_scope()
        for statement in block.children:
            if self.exit:
                context.pop_scope()
                return
            self.run_statement(statement, context)
        context.pop_scope()

    def run_statement(self, statement, context):
        """
        Run a single statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The statement to run.
            context (Context): The current context.
        """
        statement = statement.children[0]
        state_type = statement.data
        match state_type:
            case "speak_statement":
                run_speak(statement, context, self.speak_function)
            case "listen_statement":
                run_listen(statement, context, self.listen_function)
            case "if_statement":
                self.run_if(statement, context)
            case "engage_statement":
                self.run_engage(statement, context)
            case "assign_statement":
                run_assign(statement, context)
            case "end_statement":
                self.exit = True
            case "handover_statement":
                run_handover(
                    statement, context, self.speak_function, self.listen_function
                )
            case "while_statement":
                self.run_while(statement, context)
            case "store_statement":
                run_store(statement, context)
            case "fetch_statement":
                run_fetch(statement, context)
            case "block":
                self.run_block(statement, context)

    async def arun_statement(self, statement, context):
        """
        Run a single statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The statement to run.
            context (Context): The current context.
        """
        statement = statement.children[0]
        state_type = statement.data
        match state_type:
            case "speak_statement":
                await arun_speak(statement, context, self.speak_function)
            case "listen_statement":
                await arun_listen(statement, context, self.listen_function)
            case "if_statement":
                await self.arun_if(statement, context)
            case "engage_statement":
                await self.arun_engage(statement, context)
            case "assign_statement":
                run_assign(statement, context)
            case "end_statement":
                self.exit = True
            case "handover_statement":
                await arun_handover(
                    statement, context, self.speak_function, self.listen_function
                )
            case "while_statement":
                await self.arun_while(statement, context)
            case "store_statement":
                run_store(statement, context)
            case "fetch_statement":
                run_fetch(statement, context)
            case "block":
                await self.arun_block(statement, context)

    async def arun_if(self, statement, context):
        """
        Run an if statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The if statement to run.
            context (Context): The current context.
        """
        condition = statement.children[0]
        result = get_condition(condition, context)
        if result:
            await self.arun_block(statement.children[1], context)
        else:
            if len(statement.children) == 3:
                await self.arun_else(statement.children[2], context)

    def run_if(self, statement, context):
        """
        Run an if statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The if statement to run.
            context (Context): The current context.
        """
        condition = statement.children[0]
        result = get_condition(condition, context)
        if result:
            self.run_block(statement.children[1], context)
        else:
            if len(statement.children) == 3:
                self.run_else(statement.children[2], context)

    async def arun_else(self, statement, context):
        """
        Run an else statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The else statement to run.
            context (Context): The current context.
        """
        else_statement = statement.children[0]
        match else_statement.data:
            case "block":
                await self.arun_block(else_statement, context)
            case "if_statement":
                await self.arun_if(else_statement, context)

    def run_else(self, statement, context):
        """
        Run an else statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The else statement to run.
            context (Context): The current context.
        """
        else_statement = statement.children[0]
        match else_statement.data:
            case "block":
                self.run_block(else_statement, context)
            case "if_statement":
                self.run_if(else_statement, context)

    async def arun_engage(self, statement, context):
        """
        Run an engage statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The engage statement to run.
            context (Context): The current context.
        """
        flow_name = get_flow_name(statement.children[0])
        await self.arun_flow(flow_name, context.get_parameter())

    def run_engage(self, statement, context):
        """
        Run an engage statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The engage statement to run.
            context (Context): The current context.
        """
        flow_name = get_flow_name(statement.children[0])
        self.run_flow(flow_name, context.get_parameter())

    async def arun_while(self, statement, context):
        """
        Run a while statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The while statement to run.
            context (Context): The current context.
        """
        condition = statement.children[0]
        while get_condition(condition, context):
            if self.exit:
                return
            await self.arun_block(statement.children[1], context)

    def run_while(self, statement, context):
        """
        Run a while statement in the ChatFlow program.

        Args:
            statement (lark.Tree): The while statement to run.
            context (Context): The current context.
        """
        condition = statement.children[0]
        while get_condition(condition, context):
            if self.exit:
                return
            self.run_block(statement.children[1], context)
