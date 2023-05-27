
#include "kautil/algorithm/quick_sort/quick_sort.h"
#include "./cc/ui/ui.h"


struct kautil_quick_sort_handle{
    kautil::algorithm::qsort qsort;
};

static intptr_t seek_default(int64_t l,int64_t const& ofs,void * arg){ return l + ofs; }

kautil_quick_sort_handle * kautil_quick_sort_initialize(){
    auto res = new kautil_quick_sort_handle;
    return res;
}


int kautil_quick_sort_thread_arguments_alloc(kautil_quick_sort_handle * hdl,uint64_t const& number_of_thread){ return hdl->qsort.set_thread_number(number_of_thread); }
int kautil_quick_sort_thread_arguments_set(kautil_quick_sort_handle * hdl,void * arg,int const& idx){ return hdl->qsort.set_thread_argument(arg,idx); }
int kautil_quick_sort_set(
        kautil_quick_sort_handle * hdl
        ,uint64_t const& step
        ,int (*cmp)(intptr_t l,intptr_t r,void * arg)
        ,void (*swap)(intptr_t l,intptr_t r,void * arg)
        ,intptr_t (*seek)(intptr_t l,int64_t const& offset,void * arg)
        ){
    return !hdl->qsort.set(step,cmp,swap,seek) ? 0:1;
}


int kautil_quick_sort_set(
        kautil_quick_sort_handle * hdl
        ,uint64_t const& step
        ,int (*cmp)(intptr_t l,intptr_t r,void * arg)
        ,void (*swap)(intptr_t l,intptr_t r,void * arg)
        ){
    return !hdl->qsort.set(step,cmp,swap,seek_default) ? 0:1;
}


int kautil_quick_sort(kautil_quick_sort_handle *hdl, intptr_t data_begin, intptr_t data_end) {
    hdl->qsort.sort(reinterpret_cast<void*>(data_begin),reinterpret_cast<void*>(data_end));
    return 0;
}

int kautil_quick_sort(kautil_quick_sort_handle *hdl, const void *data_begin, const void *data_end) {
    hdl->qsort.sort(data_begin,data_end);
    return 0;
}

int kautil_quick_argument_set(kautil_quick_sort_handle *hdl, void *arg) {
    return !kautil_quick_sort_thread_arguments_alloc(hdl,1)
        && !kautil_quick_sort_thread_arguments_set(hdl,arg,0) ? 0:1;
}

void kautil_quick_sort_finalize(kautil_quick_sort_handle * hdl){ delete hdl; }

