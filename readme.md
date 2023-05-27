
### platform
* mingw
* msvc (not yet test on linux)

### Outline
* multithread
* possible to sort the comtents in file by using offset and seek ( for example : std::ofstream::ofs_t and it's seek* functions)
* customizable by implementing  at least two callback funcitons (cmp and swap. optionally seek) 
* extern "C" (dllimport/export) 

### examples 
* [sort data on memory and sort data in file](./examples/example_extern.cc)
* [extern(dlopen/LoadLibrary)](./examples/example_extern.cc)

### Reference 
* [forkfed from https://www.geeksforgeeks.org/cpp-program-for-quicksort](https://www.geeksforgeeks.org/cpp-program-for-quicksort/)