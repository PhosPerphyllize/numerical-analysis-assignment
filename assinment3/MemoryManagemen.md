## 函数返回的对象，其仅在执行该行中生存，下一行立即被销毁
    #include <iostream>
    class T {
    public:
        ~T() { std::cout << "destroy" << std::endl; }
    };
    
    T f() { return T(); }

    int main() {
        f(),std::cout << "first line\n";
        std::cout << "next line\n";
    }

    first line
    destroy
    next line

## 若没有重载=，则使用a=f()来初始化a，局部变量不会被销毁，作用域于a一致，且两者地址一致
    #include <iostream>
    class T {
    public:
        int num;
        ~T() { std::cout << "destroy" << std::endl; }
        T get() { return *this; }
    };

    T f() { T a=T(); std::cout << &a << std::endl; return a; }

    int main() {
        T a = f();
        std::cout << &a << std::endl;
        std::cout << "next line\n";
    }

    0x61fe0c
    0x61fe0c
    next line
    destroy

## 若正常，则a=f()中f()的局部变量按正常销毁，返回的是其拷贝
    #include <iostream>
    class T {
    public:
        int num;
        T(int v) { num=v; }
        ~T() { std::cout << "destroy" << std::endl; }
        T get() { return *this; }
    };

    T f() { T a=T(1); std::cout << &a << std::endl; return a; }

    int main() {
        T a(1);  a = f();
        std::cout << &a << std::endl;
        std::cout << "next line\n";
    }

    0x61fe0c
    destroy
    0x61fe08
    next line
    destroy

## 类中 return *this; 若返回参数不带指针引用，则返回拷贝，不是本身
    #include <iostream>
    class T {
    public:
        int num;
        ~T() { std::cout << "destroy" << std::endl; }
        T get() { return *this; }
    };

    int main() {
        T a,b;
        b = a.get();
        std::cout << &a << std::endl;
        std::cout << &b << std::endl;
    }

    destroy
    0x61fe08
    0x61fe04
    destroy
    destroy

## 函数输入若不加&也是浅拷贝的一种，fun(Mat a) 如果a内有指针，则会直接复制内容过去，函数结束时销毁。
## (但似乎也可能不销毁)，当传的类里面有指针时建议使用fun(Mat &a)
    #include <iostream>
    class T {
    public:
        int* p;
        T(int num) { p=new int[2]; *p=num;}
        ~T() { std::cout << "destroy: "<< p << std::endl; delete [] p; }
        T get() { return *this; }
    };

    void f(T t) { std::cout << t.p << std::endl; }

    int main() {
        T a(233);
        std::cout << a.p << std::endl;
        f(a);
        std::cout << a.p <<" " << *(a.p) << std::endl;
        std::cout << "Code end." <<std::endl;
        return 0;
    }

    0x632b00
    0x632b00
    destroy: 0x632b00
    0x632b00 233
    Code end.
    destroy: 0x632b00

    改成void f(T &t) { std::cout << t.p << std::endl; }后：
    0x25f2b00
    0x25f2b00
    0x25f2b00 233
    Code end.
    destroy: 0x25f2b00

## 注意在类里面，若类里有指针，则类方法返回*this时返回参数应设置为引用。
## 不然在返回时，方法会创造一个浅拷贝的副本作为返回，然后方法结束后销毁，类内部的指针也会跟着销毁。
    #include <iostream>
    class T {
    public:
        int* p;
        T(int num) { p=new int[2]; *p=num;}
        ~T() { std::cout << "destroy: "<< p << std::endl; delete [] p; }
        T get() { return *this; }
    };

    void f(T t) { std::cout << t.p << std::endl; }

    int main() {
        T a(233);
        std::cout << a.p << std::endl;
        a.get();
        std::cout << a.p <<" " << *(a.p) << std::endl;
        std::cout << "Code end." <<std::endl;
        return 0;
    }

## 有时候类内指针的越界访问也会导致在析构时出现未知错误，该错误与上面的类似