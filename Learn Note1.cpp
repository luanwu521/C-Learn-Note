﻿#include <iostream>
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

    //某些时候 我们没办法直接使用智能指针
    //比如 在调用某些C API时 只能传入一个普通指针
    //那么这时就有必要从智能指针转换成普通指针
    int* ptr3 = ptr1.get();
    //ptr3和ptr1指向同一个对象
    //但是这么做要保证操作ptr3时其所指内存不会被释放 
    //不然ptr1和ptr2跟着完蛋
    //也就是指向这块内存上的所有指针都完蛋

    //我们也可以将普通指针转成智能指针
    //转换之后 我们也没必要再使用原来的普通指针了
    //我们有更加自动化的智能指针来管理内存
    int b = 888;
    int c = 666;
    int* d = new int(c);
    shared_ptr<int> ptr4 = make_shared<int>(b);
    cout << *ptr4 << endl;//未更改前
    ptr4.reset(d);
    cout << *ptr4 << endl;//更改之后 
    //此时不再需要用d管理内存 用ptr4即可 也就是普通指针转换成了智能指针
    //这里我们注意到 给智能指针分配的内存需要是new的 也就是动态内存
    //因为我们的动态指针默认是用delete来释放内存的
    //当我们更改这个默认的释放操作时 也可以让智能指针绑定到其他类型的普通指针上
    //但一定要有一个合适的释放内存的操作来代替这个默认的delete操作
    //重载函数:ptr4.reset(d, fun) fun是一个可调用对象 用来替代delete
    
    
    return 0;
}