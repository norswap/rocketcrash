OPTIONS := -Wall -Wextra -pedantic -Werror -Wfatal-errors -I.

c90:
	gcc -c -std=c90 $(OPTIONS) rocketcrash.c

testc90: c90
	gcc -std=c90 $(OPTIONS) -o test.exe rocketcrash.o test.c
	./test.exe
	rm test.exe

c99:
	gcc -c -std=c99 $(OPTIONS) rocketcrash.c

testc99: c99
	gcc -std=c99 $(OPTIONS) -o test.exe rocketcrash.o test.c
	./test.exe
	rm test.exe

c11:
	gcc -c -std=c11 $(OPTIONS) rocketcrash.c

testc11: c11
	gcc -std=c11 $(OPTIONS) -o test.exe rocketcrash.o test.c
	./test.exe
	rm test.exe

clean:
	rm -f *.o *.obj *.exe
