#include "./internal.h"
#include "../ui/ui.h"

namespace kautil{
namespace algorithm{


void qsort_internal::_quick_sort(qsort::ptr_t start,qsort::ptr_t end,void * callback_arg){
    if(start >= end) return;
    auto p=_partition(start,end,callback_arg);
    _quick_sort(start, seek(p,-step,callback_arg),callback_arg);
    _quick_sort(seek(p,step,callback_arg),end,callback_arg);
}

void * qsort_internal::cb_thread(void * targ){
    auto arg=reinterpret_cast<thread_arg*>(targ);
    auto cb_arg =arg->callback_arg;
    auto m = arg->self->m;
    auto p=m->_partition(arg->start,arg->end,cb_arg);
    m->_mt_quick_sort(arg->start, m->seek(p,-m->step,cb_arg),cb_arg);
    m->_mt_quick_sort(m->seek(p,m->step,cb_arg),arg->end,cb_arg);
    return targ;
}


void qsort_internal::_mt_quick_sort(qsort::ptr_t start,qsort::ptr_t end,void * callback_arg){
    int tcnt = 0;
    if(start >= end) return;

    {
        std::lock_guard<std::mutex> lk(mtx);
        if(thread_cnt)tcnt = thread_cnt--;
    }

    if(tcnt) {
        auto targ =&args[thread_cnt];
        targ->start = start;
        targ->end = end;
        targ->self=self;
        targ->callback_arg= callback_args.size() > thread_cnt ? callback_args[thread_cnt] : nullptr;


        ts[thread_cnt] = std::unique_ptr<std::thread>(new std::thread(qsort_internal::cb_thread,(void *)targ));
        ts[thread_cnt]->join();

    }else{
        auto cbarg = callback_arg;
        auto p=_partition(start,end,cbarg);
        self->m->_quick_sort(start, seek(p,-step,cbarg),cbarg);
        self->m->_quick_sort(seek(p,step,cbarg),end,cbarg);
    }
}


ptr_t qsort_internal::_partition(ptr_t start, ptr_t end, void *arg) {
    ptr_t pivot = start;
    ptr_t buf = start;
    for (auto cur = seek(start, step, arg); cur <= end; cur = seek(cur, step, arg)) {
        if (cmp(cur, buf, arg) <= 0) pivot = seek(pivot, step, arg);
    }
    swap(pivot, start, arg);
    while (start < pivot && end > pivot) {
        while (cmp(start, pivot, arg) <= 0) start = seek(start, step, arg);
        while (cmp(end, pivot, arg) > 0) end = seek(end, -step, arg);
        if (start < pivot && end > pivot) swap(start, end, arg);
    }
    return pivot;
}

int qsort_internal::_sort(const void *start,const void * end){
    auto last_elem_addr = reinterpret_cast<ptr_t>(end)-step;
    if (1 == (thread_max)) {
        _quick_sort(reinterpret_cast<ptr_t>(start), last_elem_addr, callback_args.empty()? nullptr:callback_args.back());
    } else {
        thread_cnt = thread_max;
        ts.resize(thread_max);
        args.resize(thread_max);
        if (callback_args.empty()) callback_args.resize(1);
        _mt_quick_sort(reinterpret_cast<ptr_t>(start), last_elem_addr, callback_args.back());
    }
    return 0;
}


} //namespace algorithm{
} //namespace kautil{
