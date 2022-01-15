#ifndef ROCKETCRASH_H
#define ROCKETCRASH_H

#include <setjmp.h>

/******************************************************************************/

/* rocketcrash_thread_local */

#if defined ___STD_VERSION__ && __STDC_VERSION__ >= 201112L /* c11 */
    #define rocketcrash_thread_local _Thread_local
#elif defined __GNUC__ /* gcc */
    #define rocketcrash_thread_local __thread
#elif defined _MSC_VER /* microsoft c compiler */
    #define rocketcrash_thread_local __declspec(thread)
#else /* give up, single thread only */
    #define rocketcrash_thread_local
#endif

/* rocketcrash_noreturn */

#if defined ___STD_VERSION__ && __STDC_VERSION__ >= 201112L /* c11 */
    #define rocketcrash_noreturn _Noreturn
#elif defined __GNUC__
    #define rocketcrash_noreturn __attribute__ ((__noreturn__))
#elif defined _MSC_VER /* microsoft c compiler */
    #define rocketcrash_noreturn __declspec(noreturn)
#else /* give up, no compiler hint */
    #define rocketcrash_noreturn
#endif

/******************************************************************************/

struct rocketcrash_Context
{
    jmp_buf env;
    char const * exception;
    int status;
    void const * info;
};

extern rocketcrash_thread_local struct rocketcrash_Context *
    rocketcrash_context;

/* rocketcrash_context->status is a bitfield with these flags */
#define rocketcrash_THROWN     1
#define rocketcrash_CAUGHT     2
#define rocketcrash_UNSCOPED   4
#define rocketcrash_FINALIZED  8

/* UNSCOPED  : the exception occured outside of a try clause */
/* FINALIZED : the finalize clause of the try statement has been entered */

#define try \
    { \
        struct rocketcrash_Context * \
            rocketcrash_old_context; \
        struct rocketcrash_Context * \
            rocketcrash_tmp_context; \
\
        rocketcrash_old_context = rocketcrash_context; \
\
        rocketcrash_tmp_context = malloc(sizeof(struct rocketcrash_Context)); \
\
        rocketcrash_context = rocketcrash_tmp_context; \
\
        rocketcrash_context->status = 0; \
\
        if (!setjmp(rocketcrash_context->env)) {

# define catch(EXCEPTION) \
        gcatch(EXCEPTION, 1)

 #define gcatch(EXCEPTION, GUARD) \
        ccatch(rocketcrash_context->exception == EXCEPTION && (GUARD))

#define ccatch(EXPR) \
        } else if (!(   rocketcrash_context->status \
                      & rocketcrash_UNSCOPED \
                   ) \
                   && (EXPR) \
        ) { \
            rocketcrash_context->status |= \
                rocketcrash_CAUGHT;

#define finally \
        } \
        if ((   rocketcrash_context->status \
              & rocketcrash_FINALIZED \
            ) == 0 \
        ) { \
            rocketcrash_context->status |= \
                rocketcrash_FINALIZED;

#define endtry \
        } \
        { \
            char const * const rocketcrash_exception = \
                rocketcrash_context->exception; \
\
            int rocketcrash_status = \
                rocketcrash_context->status; \
\
            free(rocketcrash_context); \
\
            rocketcrash_context = \
                rocketcrash_old_context; \
\
            if ((  rocketcrash_status \
                 & rocketcrash_THROWN  ) \
\
                && (  rocketcrash_status \
                     & rocketcrash_CAUGHT \
                   ) == 0 \
            ) { \
                throw(rocketcrash_exception); \
            } \
        } \
    }

#define exception_info (rocketcrash_context->info)

#define throw(EXCEPTION) throw2(EXCEPTION, NULL)

rocketcrash_noreturn void throw2(char const * const exception, void const * const info);

#endif
