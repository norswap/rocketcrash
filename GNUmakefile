OPTIONS := -pipe -pedantic -pedantic-errors -I. -Wall -Wextra -Werror -Wfatal-errors

DEBUG ?= 0

ifeq (1,$(DEBUG))
OPTIONS += -Og -ggdb -g3 -ggnu-pubnames -D_FORTIFY_SOURCE=2 -fvar-tracking -fvar-tracking-assignments -fdebug-types-section \
-fno-eliminate-unused-debug-types -fstack-check -fstack-protector-strong -fstrict-aliasing -ftabstop=0 \
-Wabi -Waggregate-return -Waggressive-loop-optimizations -Walloc-size-larger-than=4096 -Walloc-zero -Walloca -Walloca-larger-than=4096 -Wattributes \
-Wbad-function-cast -Wbuiltin-declaration-mismatch -Wbuiltin-macro-redefined -Wcast-align -Wcast-qual -Wconversion -Wcoverage-mismatch -Wcpp -Wdate-time \
-Wdeclaration-after-statement -Wdeprecated -Wdeprecated-declarations -Wdesignated-init -Wdisabled-optimization -Wdiscarded-array-qualifiers \
-Wdiscarded-qualifiers -Wdiv-by-zero -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond -Werror-implicit-function-declaration \
-Wimplicit-fallthrough=5 -Wfloat-equal -Wformat -Wformat-signedness -Wframe-larger-than=4096 -Wfree-nonheap-object -Whsa -Wignored-attributes \
-Wincompatible-pointer-types -Winline -Wint-conversion -Wint-to-pointer-cast -Winvalid-memory-model -Winvalid-pch -Wjump-misses-init -Wlarger-than=4096 \
-Wlogical-op -Wlto-type-mismatch -Wmissing-declarations -Wmissing-include-dirs -Wmissing-prototypes -Wmultichar -Wnested-externs -Wnormalized \
-Wnull-dereference -Wodr -Wold-style-definition -Woverflow -Woverride-init-side-effects -Wpacked -Wpacked-bitfield-compat -Wpointer-compare \
-Wpointer-to-int-cast -Wpragmas -Wredundant-decls -Wrestrict -Wreturn-local-addr -Wscalar-storage-order -Wshadow -Wshift-count-negative \
-Wshift-count-overflow -Wshift-negative-value -Wshift-overflow -Wsizeof-array-argument -Wstack-protector -Wstack-usage=4096 -Wstrict-prototypes \
-Wstringop-overflow -Wsuggest-attribute=const -Wsuggest-attribute=format -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods \
-Wsuggest-final-types -Wswitch-bool -Wswitch-default -Wswitch-enum -Wswitch-unreachable -Wsync-nand -Wtrampolines -Wundef -Wunsafe-loop-optimizations \
-Wunsuffixed-float-constants -Wunused-macros -Wunused-result -Wvarargs -Wvector-operation-performance -Wvla -Wvla-larger-than=4096 -Wwrite-strings \
-Wtraditional-conversion
endif

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
