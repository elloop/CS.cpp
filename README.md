#CS.cpp
Computer Science Practice Using cpp.
---

## Projects in this repo
|*Name*| *Description*|
|------|--------------|
|[TrainingGround](https://github.com/elloop/CS.cpp/tree/master/TrainingGround) | free training place|
|[TotalSTL](https://github.com/elloop/CS.cpp/tree/master/TotalSTL)| STL practice code |
|[Algorithm](https://github.com/elloop/CS.cpp/tree/master/CS.cpp) | datastructure and algorithm practice |
|[UnderstandingCpp11](https://github.com/elloop/CS.cpp/tree/master/UnderstandingCpp11) | c++11 features demo codes from a book. |

Please check the README file in each project folder to learn more. 

## Test Framework In This Repo

`RUN_GTEST` and `BEGIN_TEST` are two macros I defined as a switch tha can control which gtest case can be tested.

codes wrapped with `RUN_GTEST` and `END_TEST` will be run.

codes wrapped with `BEGIN_TEST` and `END_TEST` won't be run, unless `SKIP_ALL_TEST` is defined.

by defining these macros, i can decide only one test case to be run without deleting other test cases' codes.

see `macro_define.h` to learn more.

## TODO

- [ ] remove jsoncpp.lib(2.1M), integrate src as a git submodule.
- [ ] remove gtestd.lib(3.5M), integrate src as a git submodule.
- [ ] use cmake to manage the project building.
- [x] create a new repo to replace this, because this repo has a too large .git folder(9M).
      After deleting `xcode` and `vim` branches, .git decrease to 3M, so I needn't create a new repo anymore.

=====================
Because the commits I do by using cmd-line tools on my local computer won't be shown in my profile contributions graph, I lost some followers who maybe think that I'm not doing my git-jobs.

So I decide to sign in here everyday, is this stupid?

Sign in with one sentence:

2016-1-22 today is the first day after our nianhui, we rest in the morning.
