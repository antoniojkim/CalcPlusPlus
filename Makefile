
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

pydep:
	cp MathEngine/libMathEngine.so calcpp/
	cp `readlink .libs/libgsl.so.25` calcpp/libgsl.so.25
	cp `readlink .libs/libgslcblas.so.0` calcpp/libgslcblas.so.0

repl: build pydep
	cd calcpp && python main.py -m ui

pyui: build pydep
	cd calcpp && python main.py -m ui

pypkg: build pydep
	cd calcpp && pyinstaller calcpp.spec

ui:
	rm -f UI/calcpp
	.utils/build_ui

run: ui
	python -u .utils/package.py --no-tar
	cd .package/CalcPlusPlus && ./Calculator

package: ui
	python -u .utils/package.py

pkg: pypkg


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
