
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
	.utils/package

sandbox:
	sandboxer --create --name $(name) --lang $(lang)

experiment:
	sandboxer --build --name $(name) --lang $(lang)


install:
	.utils/install

requirements:
	pip install -r requirements.txt

generate:
	python3 -u MathEngine/.utils/auto_generate.py

bp:  # breakpoints
	vim Tests/.gdbinit

clean:
	rm -f MathEngine/libMathEngine.a Tests/run CalcUI/CalcUI

.PHONY: clean
