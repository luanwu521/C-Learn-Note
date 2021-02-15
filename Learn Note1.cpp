#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int main()
{
    //C++中使用new和delete来管理一块动态内存
    //new可以从堆中申请一块内存 存放某个对象
    //delete将内存归还于堆 释放其中的对象
    int n = 10;//数组成员数
    //通过new实现一个动态数组
    int* arr1 = new int[n];
    //可以发现 动态数组的成员数可以使用变量 而不是常量
    //因为这是分配的运行期的堆内存 而不是编译期决定的栈内存
    //编译期决定的数组是必须要有确定的大小的 因为编译器要给它分配内存
    for (int* p = arr1; p != arr1 + n; p++) {
        *p = 666;//数组每个成员都赋值666
        printf("%d ", *p);
    }
    cout << endl;
    //当不使用一块动态内存时 要delete回收给堆
    delete[] arr1;//delete一个动态数组 要记得加上方括号[]


    //内存泄漏是程序中常见问题 通常问题是忘记delete掉new的内存
    //对于这个问题 我们可以考虑用智能指针来管理内存
    //智能指针可以在对象使用完后 自动的帮我们delete
    
    int a = 1000;
    //定义一个智能指针 管理我们的一块内存 里面存放着一个int
    shared_ptr<int> ptr1 = shared_ptr<int>(new int(a));
    //当然还有更安全的分配和使用动态内存的方法
    shared_ptr<int> ptr2 = make_shared<int>(a);
    
    printf("value_ptr1:%d \nvalue_ptr2:%d \n", *ptr1, *ptr2);
    //智能指针拥有一个计数器 可以称作引用计数
    //可以理解为 当前有多少个智能指针在使用某个对象
    //当引用计数 = 0时 也可以说是 没有智能指针在使用某个对象
    //那么最后一个shared_ptr销毁时就会自动释放这个对象
    
    //默认的shared_ptr释放对象时会使用delete
    //我们也可以自定义这个“释放”操作
    //shared_ptr<T> p(q, d);
    //定义一个智能指针p 指向q所指的地址 并且以可调用对象d来代替默认的delete
    //这个q是一个普通指针 所指类型要与T相同或可转换
    //函数是一种可调用对象 也就是说可以将函数名作为d传入 代替delete
}
