#ifndef STDDEFINES_H_
#define STDDEFINES_H_

#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// Tunables
#define L2_CACHE_LINE_SIZE          64
#define MR_LOCK_PTMUTEX
//#define TIMING
#define dprintf(...)     //fprintf(stderr, __VA_ARGS__)     // Debug printf

// Thread specific information
struct thread_loc
{
    int thread;
    int cpu;
    int lgrp;
    mutable unsigned int seed;      // thread-local random number seed
    char pad[L2_CACHE_LINE_SIZE-4*sizeof(int)];
};

/* Wrapper to check for errors */
#define CHECK_ERROR(a)                                       \
   if (a)                                                    \
   {                                                         \
      perror("Error at line\n\t" #a "\nSystem Msg");         \
      assert ((a) == 0);                                     \
   }

static inline char const* GETENV(char const* envstr)
{
   char const* env = getenv(envstr);
   if (!env) return "0";
   else return env;
}

static inline double time_diff (
    timespec const& end, timespec const& begin)
{
#ifdef TIMING
    double result;

    result = end.tv_sec - begin.tv_sec;
    result += (end.tv_nsec - begin.tv_nsec) / (double)1000000000;

    return result;
#else
    return 0;
#endif
}

static inline void get_time (timespec& ts)
{
#ifdef TIMING
    volatile long noskip;
    #if _POSIX_TIMERS > 0
        clock_gettime(CLOCK_REALTIME, &ts);
    #else
        struct timeval tv;
        gettimeofday(&tv, NULL);
        ts.tv_sec = tv.tv_sec;
        ts.tv_nsec = tv.tv_usec*1000;
    #endif
    noskip = ts.tv_nsec;
#endif
}

static inline timespec get_time()
{
    timespec t;
#ifdef TIMING
    get_time(t);
#endif
    return t;
}

static inline double time_elapsed(timespec const& begin)
{
#ifdef TIMING
    timespec now;
    get_time(now);
    return time_diff(now, begin);
#else
    return 0;
#endif
}

static inline void print_time (char const* prompt, timespec const& begin, timespec const& end)
{
#ifdef TIMING
    printf("%s : %.3f\n", prompt, time_diff(end, begin));
#endif
}

static inline void print_time (char const* prompt, double diff)
{
#ifdef TIMING
    printf("%s : %.3f\n", prompt, diff);
#endif
}

static inline void print_time_elapsed (char const* prompt, timespec const& begin)
{
#ifdef TIMING
    printf("%s : %.3f\n", prompt, time_elapsed(begin));
#endif
}

#endif // STDDEFINES_H_

// vim: ts=8 sw=4 sts=4 smarttab smartindent
