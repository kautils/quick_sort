#ifndef KAUTIL_ALGORITHM_SEARCH_EXAMPLE_EXMAPLE_QUICK_SORT_QUICK_SORT_CC_INTERNAL_H
#define KAUTIL_ALGORITHM_SEARCH_EXAMPLE_EXMAPLE_QUICK_SORT_QUICK_SORT_CC_INTERNAL_H

#include <vector>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <thread>

namespace kautil{
namespace algorithm {

using ptr_t = intptr_t;
struct qsort;

struct thread_arg{
    intptr_t start;
    intptr_t end;
    qsort * self;
    void * callback_arg;
};

struct qsort_internal{

    std::vector<std::unique_ptr<std::thread>> ts;
    std::mutex mtx;
    std::vector<thread_arg> args;
    std::vector<void * > callback_args;
    struct qsort * self;
    ptr_t step=0;
    int thread_max=1;
    int thread_cnt=0;

    int (*cmp)(ptr_t l,ptr_t r,void * arg)= nullptr;
    void (*swap)(ptr_t l,ptr_t r,void * arg) = nullptr;
    ptr_t (*seek)(ptr_t l,int64_t const& offset,void * arg)= nullptr;

    void _mt_quick_sort(ptr_t start,ptr_t end,void * callback_arg);
    void _quick_sort(ptr_t start,ptr_t end,void * callback_arg);
    int _sort(const void *start,const void * end);
    ptr_t _partition(ptr_t start,ptr_t  end,void * arg);
    static void * cb_thread(void * targ);
};


} //namespace kautil{
} //namespace algorithm {



#endif