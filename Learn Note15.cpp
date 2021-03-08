#include <iostream>
using namespace std;

class A {
public:
	int a1 = 6;
	int operator() () {
		return a1;
	}
};

class B {
public:
	int b1 = 0;
};

class C : public A, public B{//C类继承A、B类 这是多类继承
public:
	int c1 = 0;
};

class D : public virtual A{//设置D虚继承A
public:
	int d1 = 0;
};

class E : public virtual A {//设置E虚继承A
public:
	int e1 = 0;
};

class F : public D, public E {
public:
	int f1 = 0;
};

int main() {

	C demo_c1;
	//类似单类继承 多类继承也可以使用基类指针访问派生类
	A* ptr_a1 = &demo_c1;//A是C的基类 可以用A类指针或引用来绑定C类对象
	B* ptr_b1 = &demo_c1;//B是C的基类 可以用B类指针或引用来绑定C类对象
	cout << ptr_a1->a1 << endl;
	cout << ptr_b1->b1 << endl;
	//ptr_a1->c1 错误 因为ptr_a1的静态类型是A型指针 只能访问A的成员
	//ptr_b1->c1 错误 因为ptr_b1的静态类型是B型指针 只能访问B的成员

	F demo_f1;//创建一个F类型的对象
	//可以看到F同时继承了D、E 而D、E同时又继承了A 那么在F中就会存在两份A的拷贝
	//为了避免这种情况 我们会将A到D、E的继承设置成虚继承 这样就可以保证 此种情况下仅存在A的一份拷贝
	cout << demo_f1.a1 << demo_f1.d1 << demo_f1.e1 << demo_f1.f1 << endl;
	//A我们称之为虚基类 虚基类总是先于非虚基类构造的
	//构造按照派生列表从左到右的顺序进行 
	//先按照这个顺序走一遍需要继承的类 找出其中的虚基类进行构造 再走第二遍构造非虚基类
	//如F的构造:先进行A的构造 因为A是虚基类 再进行D的构造 再到E的构造 最后到F本身的构造

	
	//第一个括号代表构造一个临时的A对象
	//第二个括号代表调用临时构造的对象 
	//因为我们重载了A的调用运算符() 所以A的对象成为了一个可调用对象
	cout << A()() << endl;

	return 0;
}