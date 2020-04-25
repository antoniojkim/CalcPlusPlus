
build:
	.utils/build

test: build
	.utils/test

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

bp:  # breakpoints
	vim Tests/.gdbinit

cleanall:
	.utils/cleanall

clean:
	rm -f MathEngine/libMathEngine.a Tests/run CalcUI/CalcUI

.PHONY: clean
