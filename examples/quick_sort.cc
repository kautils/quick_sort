
#include "kautil/algorithm/quick_sort/quick_sort.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>



#define __i(i) (*reinterpret_cast<int*>(i))
#define fst(v) reinterpret_cast<std::fstream *>(v)


int file_sort_cmp(intptr_t l,intptr_t r,void * arg){
    using ofs_t = std::fstream::off_type;
    int bufl,bufr;
    fst(arg)->seekg(ofs_t(l),std::ios_base::beg);
    fst(arg)->read((char*)&bufl,sizeof(bufl));
    fst(arg)->seekg(ofs_t(r),std::ios_base::beg);
    fst(arg)->read((char*)&bufr,sizeof(bufr));
    fst(arg)->flush();
    return bufl - bufr;
}
void file_sort_swap(intptr_t l,intptr_t r,void * arg){

    int bufl,bufr;
    fst(arg)->seekg(l,std::ios_base::beg);
    fst(arg)->read((char*)&bufl,sizeof(bufl));
    fst(arg)->seekg(r,std::ios_base::beg);
    fst(arg)->read((char*)&bufr,sizeof(bufr));

    fst(arg)->seekg(l,std::ios_base::beg);
    fst(arg)->write((char*)&bufr,sizeof(bufr));
    fst(arg)->seekg(r,std::ios_base::beg);
    fst(arg)->write((char*)&bufl,sizeof(bufl));
    fst(arg)->flush();
}
intptr_t file_sort_seek(intptr_t l,int64_t const& ofs,void* arg){ return l + ofs; }

static auto base = std::vector{ int(9), 3, 4,5,100,200,300, 2, 1, 8,8,8,100,200,300,-1};
static auto _base_file = "base_file_sort_test";
const char * base_file_initialize(){
    std::ofstream of(_base_file,std::ios::binary|std::ios::trunc);
    for(auto const& el : base ) of.write((char*)&el, sizeof(el));
    return _base_file;
}

void base_file_show(){
    std::ifstream ifs(_base_file,std::ios::in|std::ios::binary);
    auto data = std::vector<int>();
    auto bytes = std::filesystem::file_size(_base_file);
    data.resize(bytes/sizeof(int));
    ifs.read((char *)data.data(),bytes);
    for(auto & elem : data) printf("%d ",elem);
    printf("\n");
}


#define OPTION_THREA_MAX_COUNT 2
int main(){



    {
        auto arr = base;
        auto file=base_file_initialize();
        auto hdl=kautil_quick_sort_initialize();
        kautil_quick_sort_thread_arguments_alloc(hdl,OPTION_THREA_MAX_COUNT);

        {// memory
            kautil_quick_sort_set( hdl
                    ,sizeof(int)
                    ,[](auto l,auto r,auto arg){ return __i(l) - __i(r); }
                    ,[](auto l,auto r,auto arg){
                        auto buf = __i(l);
                        __i(l) = __i(r);
                        __i(r) = buf;
                    }
                    ,[](auto l,int64_t const& ofs,auto arg){ return l + ofs; }
                    );
//            kautil_quick_sort(hdl,&*arr.begin(),&*arr.end()); // runtime error on msvc. mingw,unix like => arr.begin().base,arr.end().base()
            kautil_quick_sort(hdl,&arr.front(),&arr.back()+1);
        }
        for(auto & el: arr) printf("%d ", el);
        printf("\n");



        { // hard disc via std::fstream (see callback functions)
            kautil_quick_sort_set(hdl
                ,sizeof(int)
                ,file_sort_cmp
                ,file_sort_swap
                ,file_sort_seek
            );

            auto arg=std::fstream{file,std::ios::in|std::ios::out|std::ios::binary};
            kautil_quick_argument_set(hdl,&arg);
            kautil_quick_sort(hdl,0,std::filesystem::file_size(file));
        }
        kautil_quick_sort_finalize(hdl);
        base_file_show();
    }



    using sc = std::chrono::system_clock;
    auto len = 10;
    auto t = double(0);
    for(auto i = 0; i < len; ++i)
    { //  hard disc via std::fstream with thread
        auto file=base_file_initialize();


        auto hdl=kautil_quick_sort_initialize();
        auto s = sc::now();
        kautil_quick_sort_set(hdl
            ,sizeof(int)
            ,file_sort_cmp
            ,file_sort_swap
            /*,file_sort_seek*/
        );
        auto thread_number = OPTION_THREA_MAX_COUNT;
        kautil_quick_sort_thread_arguments_alloc(hdl,thread_number);
        auto ofs = std::vector<std::fstream>{};
        for(auto i = 0; i < thread_number; ++i){
            ofs.emplace_back(std::fstream{file,std::ios::in|std::ios::out|std::ios::binary});
            assert(ofs.back().is_open());
        }
        for(auto i = 0; i < thread_number; ++i) kautil_quick_sort_thread_arguments_set(hdl, &ofs[i], i);
        kautil_quick_sort(hdl,0,std::filesystem::file_size(file));

        t += (double ) (sc::now() - s).count() / len;

        kautil_quick_sort_finalize(hdl);
    }
    std::cout << t << std::endl;
    base_file_show();



    return 0;
}

