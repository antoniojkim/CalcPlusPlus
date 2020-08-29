# -*- coding: utf-8 -*-
from prompt_toolkit import PromptSession

from .MathEngine import MathEngine


def repl_main(args):
    engine = MathEngine()
    session = PromptSession()
    outputStr = ""
    while True:
        inputStr = session.prompt(">>> ")
        outputStr = engine.evaluateOutput(inputStr, outputStr)
        print(outputStr)
