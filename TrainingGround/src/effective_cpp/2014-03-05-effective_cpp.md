#Effective cpp (third edition)
---
## item2: Prefer consts, enums, and inlines to #defines.
*reason*
- define会造成代码膨胀，目标代码里替换所有define为同一个东西，重复。
- define通常没有scope的概念，也没有封装的概念
- define出来的函数有隐含的出错风险。 
```c++
#define MAX(a, b) (a) > (b) ? (a) : (b);
void f() {
	int a(1), b(0);
	MAX(++a, b);		// a 被累加两次
	MAX(++a, b+10);	// a 被累加1次
}
```

*conclusion*
- 常量：使用const或enum代替
- 函数形式的宏：改用inline函数代替

---
## item3: Use const whenever possible.
*reason*
- 避免不必要的错误，帮助编译器侦测出错误的用法。对象、函数参数、返回类型、成员函数，都可以用const来修饰。
- 对于member function，const 函数可以使const对象可以调用。

*conclusion*
- 编译器只保证bitwise constness，程序员应该做到logical constness(const成员函数不应该返回可以修改对象内部状态的引用或指针）
- 当const和non-const版本的函数有等价的实现的时候，让non-const版本调用const版本
```c++
const int& value() const {
	// ...
}
int& value() {
	return const_cast<int&>(static_cast<const T&>(*this).value());
}
```

---
## item4: Make sure that objects are initialized before they are used.
*conclusion*
- 使用member initialization list初始化类成员，以声明次数为准。
- “跨编译单元的初始化次序”问题，把non-local static对象替换为local static对象。使用reference-returning函数。

```c++
//---------------------------- use local static ----------------------------
// non-local static object in A.cpp
static Object a;
// used in B.cpp
static ObjectB b = a.getB(); // a may be uninitialized.

//---------------------------- reference-returning: local static ----------------------------
Object& getA() {
	static Object a;
   return a;
}

ObjectB& getB() {
	static ObjectB b = getA().getB();
   return b;
}
```

---
## item7: Declare destructors virtual in polymorphic base class.
*reason*
- avoid resource leak.

*conclusion*
- 为polymorphic base class声明一个virtual析构函数。如果base class带有任何的virtual函数，它就应该有一个virtual析构函数
>polymorphic base class是指：为实现“要通过base class接口来调用derived class对象”而设计的基类。

- 不是为了继承而定义的base class就不需要声明virtual析构函数，浪费空间（带virtual函数需要该class有vtbl）。并且不要继承这种不带虚析构函数的类（比如stl里面的容器）。

---
## item9: Never call virtual functions during construction or destruction.
*reason*
- 在base class构造（析构）期间，virtual函数不是virtual函数。

---
## item10: Have assignment operators return a reference to *this.
*reason*
- 可以实现连锁赋值的效果。非强制，但是这样可以与内置类型和stl保持一致。

---
## item11： Hanle assignment to self in operator=.
*conclusion*
- 使用证同测试(identity test), ( `if (this == &rhs) return *this;`)
- 为了异常安全性(exception safety)，调整语句执行顺序

```c++
Object& Object::operator=(const Object& rhs) {
	Mem * pOrig = mem_;			// save original mem;
    mem_ = new Mem(*rhs.mem_);	// if throw exception here, mem_ is still available.
    delete pOrig;
    return *this;
}
```

- copy-and-swap 技术

```c++
class Object {
	void swap(Object& rhs);
};
Object& Object::operator=(const Object& rhs) {
	Object temp(rhs);
    swap(temp);
    return *this;
}
```

---
## item13: Use objects to manage resource
>resource 包括内存、文件描述器(file description)、互斥锁、字型和画刷、数据库连接、网络sockets。

*reason*
- 程序员会容易忘记delete obj;

*conclusion*
- 使用RAII对象来防止资源泄露
>RAII: Resource Acquisition Is Initialization. 获得资源的同时立刻放进管理对象中。
管理对象析构的时候，资源会同时被释放。（如果析构函数抛出异常，参见条款8（不要让异常逃离析构函数）进行处理）

example:

```c++
// nake, without RAII.
void f() {
	Object * p = new Object();
    // ... forget to delete p;
}

// use shared_ptr<T> as a RAII object.
void f() {
	shared_ptr<Object> rP(new Object);
    // when f() return , rP is destructed and the resource it managed is freed.
}
```
**ps: shared_ptr is a `RCSP`: reference-counting smart pointer**

---
## item14: Think carefully about copying behaviour in resource-managing classes.
*conclusion*
- 禁止复制：让RAII对象继承noncopyable。
- RCSP: 对底层资源使用引用计数。

```c++
class Lock {
public:
	explicit Lock(Mutex* pm) 
    : mutexPtr(pm, unlock) {	// 指定shared_ptr的deleter为unlock。
    	lock(mutexPtr.get());
    }
private:
	std::shared_ptr<Mutex> mutexPtr;
};
```

- 复制底部资源,深拷贝
- 转移底部资源所有权，如auto_ptr.

**常用的是前两种方法**

---
## item20: Prefer pass-by-reference-to-const to pass-by-value.
*reason*
- 节省开销，避免不必要的copy constructor 和 destructor。
- 避免对象切割(slicing)
*conclusion*
- 尽量使用pass-by-reference-to-const代替pass-by-value，高效，避免slicing。
- pass-by-reference-to-const的方式不适用于：内置类型、stl的迭代器和函数对象，这些类型使用pass-by-value更为适当。
>ps: references往往以指针实现，因此pass by reference通常意味着真正传递的是指针。因此内置类型使用pass by value往往比使用pass by reference更为高效。stl的迭代器和函数对象习惯上都被设计为pass by value。

---
## 关于封装
>如果某些东西被封装，它就不再可见。越多东西被封装，越少人可以看到它。而越少人看到它，我们就有越大的弹性去改变它，因为我们的改变仅仅直接影响看到改变的那些人事物。因此，愈多东西被封装，我们改变那些东西的能力也愈大。这就是我们推崇封装的原因：它使我们能够改变事物而只影响到有限客户。

---

## item22: Declare data members private.
*reason*
- private == 不可见 == 封装 （除了friend，member function）
- public意味着不封装，不封装意味着不可改变，因为改变了就会直接影响到class的用户。
- protected并不比public的封装性好，如果修改或删掉一个protected的成员，那么所有derived class都会被破坏，因此protected的成员变量也意味着不封装。

*conclusion*
- 从封装的角度来看，class的访问类型其实只有两种：private == 封装；protected，public == 不封装；
- 应该将成员变量声明为private。这样做，可赋予客户访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证，并提供class作者充分的实现弹性。

## item23: Prefer non-member non-friend functions to member functions.
*reason*
- non-member non-friend functions 不增加private成员的访问次数，意味着更好的封装性（较之于member function和friend function）。
*conclusion*
- 从封装角度来看，尽量使用non-member non-friend函数替换member函数。这样不破坏封装性，增加包裹弹性和技能扩充性。
>为什么non-member non-friend functions的封装性更好呢？ 
从item22说起，成员变量应该是private的，因为如果不是，就有无限量的函数可以访问它们，它们也就毫无封装性。我们可以这样来衡量封装性：能直接访问（private）数据成员的函数越多，我们就说数据的封装性越低。能够访问private成员的函数只有两种，friend和member函数。而non-member non-friend函数并没有增加private直接被访问的次数，因此说它有更好的封装性。也正因为如此，在firend和member函数，与non-member non-friend函数之间选择，后者更受欢迎。



