#ifndef KAUTIL_ALGORITHM_SEARCH_EXAMPLE_EXMAPLE_QUICK_SORT_QUICK_SORT_CC_BASE_H
#define KAUTIL_ALGORITHM_SEARCH_EXAMPLE_EXMAPLE_QUICK_SORT_QUICK_SORT_CC_BASE_H

#include <cstdint>

namespace kautil{
namespace algorithm{
struct qsort_internal;
struct qsort{
    friend qsort_internal;
    using ptr_t = intptr_t;
    qsort();
public:
    ~qsort();
    int set_thread_number(int const& thread_limit);
    int set_thread_argument(void * callback_arg,int const& index);
    int set(
        uint64_t const& step
        ,int (*cmp)(ptr_t l,ptr_t r,void * arg)
        ,void (*swap)(ptr_t l,ptr_t r,void * arg)
        ,ptr_t (*seek)(ptr_t l,int64_t const& offset,void * arg));
    int sort(const void * start,const void * end);
private:
    qsort_internal * m;
};




} //namespace algorithm{
} //namespace kautil{



#endif