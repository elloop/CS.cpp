# understanding-cpp11
---
c++ programming examples using c++11. Partly use the gtest framework.
![Solution Overview](http://7xi3zl.com1.z0.glb.clouddn.com/solution_overview.png "Solution Overview")

#项目简介
此项目是《深入理解c++11》这本书的一个总结。
由若干个短小的测试用例组成，展示了`c++11`主要的新特性的使用方法和注意事项。其中大部分例子的原型取自该书的代码片段，加入了自己的一些理解和改编。
当前的文件列表如图：
![Topic Overview](http://7xi3zl.com1.z0.glb.clouddn.com/topic_overview.png "Topic Overview")


#开发环境
`master`分支的开发环境是Visual Studio 2013(windows8.1 64bit, _MSC_VER == 1800)，Visual AssistantX 10.9插件.
部分vc++编译器不支持的特性代码(如constexpr，user define literal等），使用了`_MSC_VER`选项进行了条件编译处理。
`xcode_and_ubuntu`分支将使用`clang++`进行编译测试。
后面将会只保留一个`master`分支，使用CMake的方式来做到跨平台构建。

#测试框架
测试框架使用的是*Google*的`c++`单元测试框架`gtest`，版本是1.7.0。为了简单，使用静态库+header的方式引入。已经在.sln中配置好了，clone下来即可使用。
此外，较早提交的文件使用的是自己写的一个小的测试框架，基类叫`Messi`, 待测试的类都继承`class Messi`,并且实现其`run`方法。测试的启动点在main.cpp里面的
`ELLOOP_TEST`宏。
内存泄露检查使用了vs自带的`crtdbg`。详见main.cpp.
![Memory Check](http://7xi3zl.com1.z0.glb.clouddn.com/memory_leak_check.png "Memory Check")

#License
Files under /include/gtest/ and /libs/gtestd.lib is copied and build from Google's unit test framework - gtest.
The license is put in root dir called LICENSE-FOR-gtest(Google).

Other parts of this repository are NOT Licensed. ALL FREE.
