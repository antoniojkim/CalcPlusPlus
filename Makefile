
build: generate
	.utils/build MathEngine $(name)

generate:
	python3 -u MathEngine/.utils/auto_generate.py

test: build
	.utils/build Tests
	.utils/test $(name)

bp:  # breakpoints
	vim Tests/.gdbinit

newtest:
	python3 -u .utils/new_test.py --name $(name)

repl: build
	.utils/build_repl

ui:
	rm -f CalcUI/CalcUI
	.utils/build_ui

# run: build ui
# 	.utils/run

run: package
	.package/CalcPlusPlus/Calculator

debug: build ui
	gdb -q -ex="run" ./CalcUI/CalcUI


package:
	python -u .utils/package.py

pkg: package


buildwin:
	powershell.exe -noprofile -executionpolicy bypass -file .utils/build.ps1


sandbox:
	sandboxer --create --name $(name) --lang $(lang)

experiment:
	sandboxer --build --name $(name) --lang $(lang)

exp: experiment

pyexp:
	sandboxer --build --name $(name) --lang python


install:
	.utils/install

requirements:
	pip install -r requirements.txt

lc:
	.utils/linecount


cleanui:
	cd CalcUI && make -f Makefile clean
cleanengine:
	cd MathEngine && make -f Makefile clean
cleantest:
	rm Tests/Tests/EngineTest.o
cleanall: cleanui cleanengine

clean:
	rm -f MathEngine/libMathEngine.a Tests/run Tests/Tests/EngineTest.o CalcUI/CalcUI

.PHONY: clean
