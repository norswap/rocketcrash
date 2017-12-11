# Rocket Crash

<img src="https://raw.githubusercontent.com/norswap/rocketcrash/master/rocketcrash.png" align="right"/>

> For here, am I sitting in a tin can  
> Far above the world  
> Planet Earth is blue  
> And there's nothing I can do 

Rocket Crash lives online at [https://github.com/norswap/rocketcrash][1].

[1]: https://github.com/norswap/rocketcrash

Rocket Crash is a C exception library build on top of
[setjmp/longjmp][setjmp.h]. There are [a lot of those][c_exception_libs]. Rocket
Crash distinguishes itself by being minimal while staying practical, in keeping
with the C philosophy.

Rocket Crash supplies a `try` statement with optional `catch` and `finally`
clauses, as well as a `throw(exception)` function. And that's it: Rocket Crash
is not an error handling framework but a simple exception construct.

Exceptions are represented by `char` pointers. In this way, we can derive a
unique exception handles by declaring a char arraywhile also supplying a short
description of the exception:

    char const STACK_OVERFLOW [] = "Stack Overflow";

Here are a some other defining characteristics:

- easy to understand
- simple: about 100 lines of code
- multi-threading support with C11, GCC or Microsoft C
- avoids namespace pollution through the use of the `rocketcrash` prefix
- `try` statements can be freely nested within all clauses, both lexically and
  accross the call stack
- it is possible to customize the conditions under which an exception is caught
- liberal (BSD) license
- compatible with C90, C99 and C11

[setjmp.h]: pubs.opengroup.org/onlinepubs/9699919799/basedefs/setjmp.h.html
[c_exception_libs]: https://code.google.com/p/exceptions4c/wiki/alternatives

## Installation

Compile using the supplied makefiles, for GNU make and Microsoft nmake:

    make c90
    make c99
    make c11
    nmake

You can also build and run the tests:

    make testc90
    make testc99
    make testc11
    nmake test

If you want to compile/test with a long list of debug-flags enabled
(presently only with recent versions of GNU Make and GCC) do:

    make DEBUG=1 c90
    make DEBUG=1 c99
    make DEBUG=1 c11

## Basic Use

A `try` statement looks like this:

    try {
        // code to try
    }
    catch (STACK_OVERFLOW) {
        // something bad happend, better do something about it!
    }
    finally {
        // perform cleanup here
    } endtry

There can be 0 or more catch clauses. The `finally` clause is optional.

You throw an exception by using:

    void throw (char *exception);

When an exception is thrown from the body of the `try` clause, the body of the
first `catch` clause that matches the thrown exception is executed, if
any. Then, if a `finally` clause is present, its body is executed. If the
exception wasn't caught, it is re-thrown so that it can be handled by an
enclosing `try` statement, if any.

If an exception is thrown (or re-thrown) and there are no enclosing `try`
statements, the program exits with an error message that mentions the name of
the exception.

If an exception is thrown from within a `catch` clause, the body of the
`finally` clause is executed if present, and this new exception is re-thrown. If
an exception is thrown from a `finally` clause, it is also re-thrown.

If Rocket Crash cannot allocate memory using `malloc()`, it throws an exception
called `ROCKETCRASH_OUT_OF_MEMORY` from the `try` statement.

__IMPORTANT__: you should not use any of `return`, `break`, `continue`,
`setjmp()` or `longjmp()` inside the `try` statement (in all clauses). `goto`
that jump within the same clause body are fine, others are not.

__IMPORTANT__: because Rocket Crash uses `setjmp()` and `longjmp()`, variables
(1) local to a function containing a `try` statement (2) that are modified
between entering the `try` statement and the time where an exception can
potentially be thrown, must be declared `volatile`.

## Advanced Features

If you want to associate some info with an exception that is being thrown, you
can do so by using `throw2(exception, info)` instead of `throw(exception)`.
`info` is a user-defined pointer. You can retrieve the info associated to an
exception inside a catch clause by using the macro `exception_info`.

Instead of `catch(exception)`, one can use `gcatch(exception, guard)` or
`ccatch(expression)` to decide whether an exception is caught.

`gcatch(exception, guard)` catches the exception if it matches and if the guard
expression is truthy.

`ccatch(expr)` catches the exception if the guard expression is truthy. This can
be used when the exception doesn't matter, or to implement advanced matching by
using implementation variables.

You are encouraged to build upon the implementation, or even modify it to suit
your needs!

## Namespace

Rocket Crash defines the following macros: `try`, `catch`, `gcatch`, `ccatch`,
`finally`, `endtry`, `throw`, `exception_info`, and the following functions:
`throw2`. It also reserves the use of all identifiers starting with
`rocketcrash_`.

## But why do I need exceptions?

When following a strict error checking hygiene (as you should), the code can
soon be overtaken by error checking code. The problem is that error codes need
to be checked at each level in the call stack between the error site and the
location where the error can be handled. With an exception mechanism, we can
bypass these intermediate checks.

## License

Rocket Crash is licensed under the [BSD 3-Clause License][bsd].

[bsd]: http://opensource.org/licenses/BSD-3-Clause

## Acknowledgements

The Rocket Crash logo was made by combining icons from
[Antonis Makriyannis][rocket_icon] and [Nolan Paparelli][crash_icon].

[rocket_icon]: http://thenounproject.com/term/rocket/1758/
[crash_icon]: http://thenounproject.com/term/fire/35234/
