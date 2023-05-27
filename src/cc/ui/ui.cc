
#include "../internal/internal.h"
#include "./ui.h"

namespace kautil{
namespace algorithm {

qsort::qsort() : m(new qsort_internal)  {}
qsort::~qsort() { delete m; }

int qsort::set_thread_number(int const &thread_limit) { m->callback_args.resize(m->thread_max = thread_limit); return 0; }
int qsort::set_thread_argument(void *callback_arg, int const &index) {
    if (m->callback_args.size() > index) {
        m->callback_args.at(index) = callback_arg;
        return 0;
    } else return 1;
}


int qsort::set(
    uint64_t const& step
    ,int (*cmp)(ptr_t l,ptr_t r,void * arg)
    ,void (*swap)(ptr_t l,ptr_t r,void * arg)
    ,ptr_t (*seek)(ptr_t l,int64_t const& offset,void * arg)
            ){
    m->step=static_cast<intptr_t>(step);
    m->cmp=cmp;
    m->swap=swap;
    m->seek=seek;
    m->self=this;
    return 0;

}


int qsort::sort(const void *start, const void * end) { return m->_sort(start,end); }





} //namespace algorithm {
} //namespace kautil{
