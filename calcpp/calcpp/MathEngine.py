# -*- coding: utf-8 -*-
import ctypes


lib = ctypes.CDLL("libMathEngine.so", mode=1)

lib.new_MathEngine.restype = ctypes.c_void_p
lib.delete_MathEngine.argtypes = [ctypes.c_void_p]

lib.evaluateOutput.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
lib.evaluateOutput.restype = ctypes.c_char_p


class MathEngine:
    def __init__(self):
        self.obj = lib.new_MathEngine()

    def __del__(self):
        lib.delete_MathEngine(self.obj)

    def evaluateOutput(self, input, output=""):
        return lib.evaluateOutput(
            self.obj,
            ctypes.c_char_p(str(input).encode("utf-8")),
            ctypes.c_char_p(str(output).encode("utf-8")),
        ).decode()
