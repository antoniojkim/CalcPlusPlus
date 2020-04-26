
build:
	.utils/build MathEngine

test: build cleantest
	.utils/build Tests
	gdb -q -ex="run" Tests/run

bp:  # breakpoints
	vim Tests/.gdbinit

newtest:
	python3 -u .utils/new_test.py --name $(name)


ui:
	.utils/build_ui

run: build ui
	./CalcUI/CalcUI

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

generate:
	python3 -u MathEngine/.utils/auto_generate.py


cleanui:
	cd CalcUI && make clean
cleanengine:
	cd MathEngine && make clean
cleantest:
	rm -f Tests/Tests/EngineTest.o
cleanall: cleanui cleanengine cleantest

clean:
	rm -f MathEngine/libMathEngine.a Tests/run Tests/Tests/EngineTest.o CalcUI/CalcUI

.PHONY: clean
