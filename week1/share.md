#C++编译器什么情况下会为类生成默认的构造函数？

曾经上C++课程的时候，课本上说：当类作者为显式声明类的任何一个构造函数时，编译器就会为类生成一个默认的构造函数。然而真的时这样吗？

C++ Annotated Reference Manual（ARM）[ELLIS90]中的Section21.1告诉我们：“default constructors 在需要的时候被编译器产生出来”。“在需要的时候”具体时什么时候呢，又是被谁需要呢？

    class Foo{public: int val; Foo* pnext};
    Foo bar;
这个时候会产生默认构造函数吗？ **答案是不会**

首先解答下上面的第二个问题，被谁需要？ **被编译器需要**
那上面的类为何编译器不需要构造函数呢？ **因为生成的构造函数将是tirvial（无用的=）的**；  bitwise copies已经足够； 所以就更要自作多情的以为*默认构造函数*（实际上并不会有）会将成员变量初始化为你以为的默认值；那是程序员要做的时，并不是编译器

那到底什么样的类在没有显式声明构造函数的情况下，编译器会生成默认的构造函数呢？默认的构造函数内，又会做些什么呢？

###1. 带有Default Constructor 的 Member Class Objest
    class Foo{public: Foo();};
    class Bar{public: Foo foo; char *str;};
以上情况，若有Bar类的构造函数需要被调用是，则编译器会生成默认的构造函数。
被生成的default contructor 看起来可能像这样

    inline Bar::Bar(){ foo.Foo::Foo();  //c++伪代码}
那如果已存在一个构造函数，但是并没有显式调用Foo构造函数的情况下，编译器会怎么做的？
编译器会保证类中的每个member class objects都调用起defautl constructor。**并且调用是在程序员的代码之前，按类成员变量在类中声明的顺序**。

###2. 带有Default Constructor 的Base Class
这个也比较容易理解，因为编译器需要调用base class的default constructor

###3. 带一个Virtual Function 的 Class
   
那编译器对这种情况做些什么呢？
1. 一个virtual function table（vtbl）会被编译器生成，内存放class的virtual function地址
2. 在每一个class object中，一个额外的pointer member（vptr）会被编译器合成出来，指向vtbl （这就是构造函数中需要干的事）

###4. 带有一个Virtual Base Class 的 Class
    class X{public: int i;}
    class A:public virtual X{public: int j};
    class B:public vitrual X{public: double d;};
    class C:public A, public B{public: int k};
    //无法在编译器决定出pa->X::i的位置
    void foo{const A* pa}{pa->i = 1024;}

为了解决这个问题，cfront的做法是靠“在derived class object的每一个virtual base classes中安插一个指针”，所有经由reference 或者 pointer来存取一个virtaul base class 都通过该指针来完成

    //可能的编译器转变操作
    void foo{const A* pa}{pa->_vbcX->i = 1024;}
所以，这个_vbcX也是需要在类的构造函数中完成初始化的。

综上，编译器所做的工作一定是**有用的（nontrivial）**，并且只会做属于它的工作，像成员变量默认值初始化这种事，就不要指望编译器了，还是自己在设计类的时候就写好吧。
    