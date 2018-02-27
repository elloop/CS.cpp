#CS.cpp
Computer Science Practice Using cpp.
---

## Projects in this repo

|*Name*| *Description*|
|------|--------------|
|[Algorithm](https://github.com/elloop/CS.cpp/tree/master/CS.cpp) | datastructure and algorithm practice |
|[TrainingGround](https://github.com/elloop/CS.cpp/tree/master/TrainingGround) | free training place|
|[TotalSTL](https://github.com/elloop/CS.cpp/tree/master/TotalSTL)| STL practice codes |
|[UnderstandingCpp11](https://github.com/elloop/CS.cpp/tree/master/UnderstandingCpp11) | c++11 features demo codes. |
|[util](https://github.com/elloop/CS.cpp/tree/master/util) | self-written util functions. |
|[c_language](https://github.com/elloop/CS.cpp/tree/master/c_language) | c language temp test codes.|

Please check the README file in each project folder to learn more. 

## How to run these codes?

### branch master : building with cmake (version 3.0+).

#### OS X (without using Xcode)

`python build_all.py -p unix`

This script will create a folder (containing the generated Makefile) called `build`  in each project's root dir.

For example, after running the python script, the structure of project Algorithm will be:


```c++

total 8
drwxr-xr-x   5 lina  staff   170B  4 24 23:05 .
drwxr-xr-x  16 lina  staff   544B  4 24 23:04 ..
-rw-r--r--   1 lina  staff   2.5K  4 24 09:19 CMakeLists.txt
drwxr-xr-x   2 lina  staff    68B  4 24 23:05 build
drwxr-xr-x  11 lina  staff   374B  4 19 11:50 src

```

then, you can go to build dir, and run `make`, executables will be output into a folder called `build` in the root dir of this repo.

#### OS X (using Xcode)

- [] todo: `python build_all.py -p mac`

#### windows (using visual studio )

`python build_all.py -p windows`

This will use `Visual Studio 12 2013 Win64` as `CMAKE_GENERATOR` value. You can change the version of visual studio in `build_all.py`.

After running this script, .sln file will be generated in the root dir of ecah project, also put in a folder called `build`.

## difference between branches

|*Name*| *Description*|
|------|--------------|
|master| building with CMake |
|1.0(visual studio)| building with visual studio |

## Test Framework In This Repo

`RUN_GTEST` and `BEGIN_TEST` are two macros I defined as a switch that can control which gtest case can be tested.

codes wrapped with `RUN_GTEST` and `END_TEST` will be run.

codes wrapped with `BEGIN_TEST` and `END_TEST` won't be run, unless `SKIP_ALL_TEST` is defined.

by defining these macros, i can decide only one test case to be run without deleting other test cases' codes.

see `macro_define.h` to learn more.

Please check this article to learn more about the test case control macro: [controlling gtest case using macro. 使用宏来作为C++单元测试开关](http://blog.csdn.net/elloop/article/details/50591827).

## TODO

- [x] remove jsoncpp.lib(2.1M), integrate src as a git submodule.

    progress: 1. jsoncpp removed, substitued by rapidjson.

- [x] remove gtestd.lib(3.5M), integrate src as a git submodule.

    progress: 1. use gtest 1.7 source codes instead of git submodule.

- [x] use cmake to manage the project building.
    
    progress: 1. branch master can be build with cmake and make on Unix now.

- [x] create a new repo to replace this, because this repo has a too large .git folder(9M).

    progress: 1.After deleting `xcode` and `vim` branches, .git decrease to 3M, so I needn't create a new repo anymore.

can i fix this ?
