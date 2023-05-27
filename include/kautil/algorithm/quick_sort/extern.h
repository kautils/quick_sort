

#include <stdint.h>

#if !defined(_MSC_BUILD)
#undef KAUTIL_QUICK_SORRT_PREFIX
#define KAUTIL_QUICK_SORRT_PREFIX extern "C"
#endif

KAUTIL_QUICK_SORRT_PREFIX void* _kautil_quick_sort_initialize();
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_thread_arguments_alloc( void* hdl,uint64_t const& number_of_thread);
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_thread_arguments_set(void* hdl,void * arg,int const& idx);

/// @note cmp is assumed returns 0, 0 < or 0 >
/// 0   : l == r
/// 0 < : l < r
/// 0 > : l > r
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_set_v2(
        void* hdl
        ,uint64_t const& step
        ,int (*cmp)(intptr_t l,intptr_t r,void * arg)
        ,void (*swap)(intptr_t l,intptr_t r,void * arg)
        ,intptr_t (*seek)(intptr_t l,int64_t const& offset,void * arg)
        );

KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_set(
        void* hdl
        ,uint64_t const& step
        ,int (*cmp)(intptr_t l,intptr_t r,void * arg)
        ,void (*swap)(intptr_t l,intptr_t r,void * arg)
        );

KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_intptr(void* hdl,intptr_t data_begin,intptr_t data_end);
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_voidptr(void* hdl,const void * data_begin,const void * data_end);
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_argument_set(void* hdl,void * arg);
KAUTIL_QUICK_SORRT_PREFIX void _kautil_quick_sort_finalize(void* hdl);


