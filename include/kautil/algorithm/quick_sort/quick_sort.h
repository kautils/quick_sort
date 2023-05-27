#ifndef KAUTIL_QUICK_SORT_QUICK_SORT_QUICK_SORT_H
#define KAUTIL_QUICK_SORT_QUICK_SORT_QUICK_SORT_H

#include <stdint.h>

struct kautil_quick_sort_handle;
kautil_quick_sort_handle * kautil_quick_sort_initialize();
int kautil_quick_sort_thread_arguments_alloc(kautil_quick_sort_handle * hdl,uint64_t const& number_of_thread);
int kautil_quick_sort_thread_arguments_set(kautil_quick_sort_handle * hdl,void * arg,int const& idx);

/// @note cmp is assumed returns 0, 0 < or 0 >
/// 0   : l == r
/// 0 < : l < r
/// 0 > : l > r
int kautil_quick_sort_set(
        kautil_quick_sort_handle * hdl
        ,uint64_t const& step
        ,int (*cmp)(intptr_t l,intptr_t r,void * arg)
        ,void (*swap)(intptr_t l,intptr_t r,void * arg)
        ,intptr_t (*seek)(intptr_t l,int64_t const& offset,void * arg)
        );

int kautil_quick_sort_set(
        kautil_quick_sort_handle * hdl
        ,uint64_t const& step
        ,int (*cmp)(intptr_t l,intptr_t r,void * arg)
        ,void (*swap)(intptr_t l,intptr_t r,void * arg)
        );

int kautil_quick_sort(kautil_quick_sort_handle* hdl,intptr_t data_begin,intptr_t data_end);
int kautil_quick_sort(kautil_quick_sort_handle* hdl,const void * data_begin,const void * data_end);
int kautil_quick_argument_set(kautil_quick_sort_handle * hdl,void * arg);
void kautil_quick_sort_finalize(kautil_quick_sort_handle *);




#endif