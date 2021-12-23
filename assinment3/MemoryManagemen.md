## �������صĶ��������ִ�и��������棬��һ������������
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

## ��û������=����ʹ��a=f()����ʼ��a���ֲ��������ᱻ���٣���������aһ�£������ߵ�ַһ��
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

## ����������a=f()��f()�ľֲ��������������٣����ص����俽��
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

## ���� return *this; �����ز�������ָ�����ã��򷵻ؿ��������Ǳ���
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

## ��������������&Ҳ��ǳ������һ�֣�fun(Mat a) ���a����ָ�룬���ֱ�Ӹ������ݹ�ȥ����������ʱ���١�
## (���ƺ�Ҳ���ܲ�����)����������������ָ��ʱ����ʹ��fun(Mat &a)
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

    �ĳ�void f(T &t) { std::cout << t.p << std::endl; }��
    0x25f2b00
    0x25f2b00
    0x25f2b00 233
    Code end.
    destroy: 0x25f2b00

## ע���������棬��������ָ�룬���෽������*thisʱ���ز���Ӧ����Ϊ���á�
## ��Ȼ�ڷ���ʱ�������ᴴ��һ��ǳ�����ĸ�����Ϊ���أ�Ȼ�󷽷����������٣����ڲ���ָ��Ҳ��������١�
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

## ��ʱ������ָ���Խ�����Ҳ�ᵼ��������ʱ����δ֪���󣬸ô��������������