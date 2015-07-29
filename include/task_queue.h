#ifndef TASK_Q_
#define TASK_Q_

#include <deque>

#include "stddefines.h"

class lock;

class task_queue
{
public:

    struct task_t {
        uint64_t        id;
        uint64_t        len;
        uint64_t        data;
        uint64_t        pad;
    };

    task_queue(int sub_queues, int num_threads);
    ~task_queue();

    void enqueue(task_t const& task, thread_loc const& loc, 
        int total_tasks=0, int lgrp=-1);
    void enqueue_seq(task_t const& task, int total_tasks=0, int lgrp=-1);
    int dequeue(task_t& task, thread_loc const& loc);

private:

    int             num_queues;
    int             num_threads;
    std::deque<task_t>* queues;
    lock**          locks;
};

#endif /* TASK_Q_ */

// vim: ts=8 sw=4 sts=4 smarttab smartindent
