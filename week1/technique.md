[理解模版类型推导](https://www.kancloud.cn/kangdandan/book/169970)

模版函数

    template<typename T>
    void f(ParamType param);
调用

    f(expr);                    // 用一些表达式来调用f
在编译的时候，编译器通过expr来进行推导出两个类型：一个是T的，另一个是ParamType。通常来说这些类型是不同的，因为ParamType通常包含一些类型的装饰，比如const或引用特性。

一般会很自然的期望T的类型和传递给他的参数的类型一致，也就是说T的类型就是expr的类型。在上面的例子中，x是一个int，T也就被推导成int。但是并不是所有的情况都是如此。T的类型不仅和expr的类型独立，而且还和ParamType的形式独立。

有趣的是，声明数组的引用可以使的创造出一个推导出一个数组包含的元素长度的模板：

    // 在编译的时候返回数组的长度（数组参数没有名字，
    // 因为只关心数组包含的元素的个数）
    template<typename T, std::size_t N>
    constexpr std::size_t arraySize(T (&)[N]) noexcept
    {
        return N;                   // constexpr和noexcept在随后的条款中介绍
    }

###要记住的东西
    1. 在模板类型推导的时候，有引用特性的参数的引用特性会被忽略
    2. 在推导通用引用参数的时候，左值会被特殊处理
    3. 在推导按值传递的参数时候，const和/或volatile参数会被视为非const和非volatile
    4. 在模板类型推导的时候，参数如果是数组或者函数名称，他们会被退化成指针，除非是用在初始化引用类型
