#include "rocketcrash.h"
#include <stdlib.h> /* EXIT_FAILURE */
#include <stdio.h>  /* fprintf */

rocketcrash_thread_local struct rocketcrash_Context * rocketcrash_context = NULL;

rocketcrash_noreturn void throw2(char const * const exception, void const * const info)
{
    if (rocketcrash_context == NULL) {
        fprintf(stderr, "Uncaught exception: %s\n", exception);
        exit(EXIT_FAILURE);
    }

    rocketcrash_context->exception = exception;
    rocketcrash_context->info = info;

    if (rocketcrash_context->status & rocketcrash_THROWN
    ||  rocketcrash_context->status & rocketcrash_FINALIZED) {
        rocketcrash_context->status |= rocketcrash_UNSCOPED;
    }

    rocketcrash_context->status |= rocketcrash_THROWN;
    rocketcrash_context->status &= ~rocketcrash_CAUGHT;
    longjmp(rocketcrash_context->env, 1);
}
