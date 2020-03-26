
build:
	.utils/build

test: build
	.utils/test

sandbox:
	python3 -u Sandboxer/sandboxer.py --create --name $(name) --lang $(lang)

experiment:
	python3 -u Sandboxer/sandboxer.py --build --name $(name) --lang $(lang)


install:
	.utils/install

tokens:
	python3 -u MathEngine/.utils/generate_tokens.py

bp:  # breakpoints
	edit Tests/.gdbinit

clean:
	rm -f MathEngine/libMathEngine.a Tests/run
.PHONY: clean
