
build:
	.utils/build

test: build
	.utils/test

ui:
	.utils/build_ui

run: ui
	./CalcUI/CalcUI

sandbox:
	python3 -u Sandboxer/sandboxer.py --create --name $(name) --lang $(lang)

experiment:
	python3 -u Sandboxer/sandboxer.py --build --name $(name) --lang $(lang)


install:
	.utils/install

generate:
	python3 -u MathEngine/.utils/auto_generate.py

bp:  # breakpoints
	edit Tests/.gdbinit

clean:
	rm -f MathEngine/libMathEngine.a Tests/run
.PHONY: clean
