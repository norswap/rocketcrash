/* This tests individual exception handling scenarios. Not all possible
scenarios can be tested, this will have to do. */

#include "rocketcrash.h"
#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* EXIT_SUCCESS */

static int thrown;
static int caught;
static int finally_done;
static int checked;
static int end_catch;
static int end_finally;
static int bar_caught;
static int after_finally;

static void reset(void)
{
    thrown          = 0;
    caught          = 0;
    finally_done    = 0;
    checked         = 0;
    end_catch       = 0;
    end_finally     = 0;
    bar_caught      = 0;
    after_finally   = 0;
}

char *foo = "foo";
char *bar = "bar";

/* can be used as an expression that throws bar and returns foo */
static char * whoops(void)
{
    throw(bar);
    return foo;
}

/* throw in try clause */
static void test01(void)
{
    reset();

    try {
        throw(foo);
    }
    catch(foo) {
        caught = 1;
    }
    finally {
        finally_done = 1;
    } endtry

    assert(caught && finally_done);
}

/* throw in catch expression */
static void test02(void)
{
    reset();

    try {
        try {
            throw(foo);
        }
        catch(whoops()) {
            caught = 1;
        }
        finally {
            finally_done = 1;
        } endtry

        after_finally = 1;
    }
    catch(bar) {
        checked = 1;
        assert(!caught && finally_done && !after_finally);
    } endtry

    assert(checked);
}

/* throw in catch clause */
static void test03(void)
{
    reset();

    try {
        try {
            throw(foo);
        }
        catch(foo) {
            caught = 1;
            throw(bar);
            end_catch = 1;
        }
        finally {
            finally_done = 1;
        } endtry

        after_finally = 1;
    }
    catch(bar) {
        checked = 1;
        assert(caught && finally_done && !end_catch && !after_finally);
    } endtry

    assert(checked);
}

/* throw in finally clause */
static void test04(void)
{
    reset();

    try {
        try {
        } finally {
            throw(foo);
            end_finally = 1;
        } endtry
    }
    catch(foo) {
        checked = 1;
        assert(!end_finally);
    } endtry

    assert(checked);
}

/* throw in try clause, two catch clauses */
static void test05(void)
{
    reset();

    try {
        throw(foo);
    }
    catch(bar) {
        bar_caught = 1;
    }
    catch(foo) {
        caught = 1;
    }
    finally {
        finally_done = 1;
    } endtry

    assert(caught && finally_done && !bar_caught);
}

/* uncaught nested throw */
static void test06(void)
{
    reset();

    try {
        try {
            throw(foo);
        }
        catch (bar) {
            bar_caught = 0;
        }
        finally {
            finally_done = 1;
        } endtry

        after_finally = 1;
    }
    catch(foo) {
        caught = 1;
    }
    finally {
        end_finally = 1;
    } endtry

    assert(caught && !bar_caught && finally_done && end_finally
        && !after_finally);
}

int main(void)
{
    test01(); printf("1"); fflush(stdout);
    test02(); printf("2"); fflush(stdout);
    test03(); printf("3"); fflush(stdout);
    test04(); printf("4"); fflush(stdout);
    test05(); printf("5"); fflush(stdout);
    test06(); printf("6"); fflush(stdout);
    printf("\nRocket Crash: All tests passed.\n");
    return EXIT_SUCCESS;
}
