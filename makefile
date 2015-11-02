# Run this using Microsoft nmake.

# C4456: declaration hides previous local declaration
# C4710: function not inlined

ms:
	@echo "Make sure the path is properly setup before running this."
	@echo "This can be achieved by running vcvarsall.bat, for instance."
	cl /nologo /c /Wall /wd4710 rocketcrash.c

test: ms
	cl /nologo /Wall /wd4456 /wd4710 test.c rocketcrash.obj
	test.exe
	rm test.exe

clean:
	rm -f *.o *.obj *.exe
