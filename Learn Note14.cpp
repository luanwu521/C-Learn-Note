#include <iostream>
#include <tuple>
#include <string>
using namespace std;

template <typename T> class C;//前置声明 表明C是一个模板类 否则编译器不认识C<T>
template <typename T> class A {
	template <typename X> friend class B;//B的所有类型实例都是A的友元
	//这里用了X 一个新的模板参数 不同于T 目的是指出B类型的任意性 而不是要求B与A类型相同
	friend class C<T>;//这里用了T 指出当C的类型和A的类型一样时 C才能成为A的友元 需要前置声明
	friend class D;//D是一个普通类 D是A的友元 不需要前置声明
public:
	int a1;
private:
	int a2;
};

template <typename T> class B {
public:
	
};

template <typename T> class C {
public:
	
};

class D {
public:
	
};

//typedef是不支持模板参数T的 typedef A<T> A2; 这样是不允许的
//但是可以typedef A<int> A3; 当T确定后(这里是int)是可以的 因为这已经是实例化模板了
//要想使模板拥有别名且可以使用模板参数T 可以使用using
template <typename T> using tuple_three_T = tuple<T, T, T>;
template <typename T> using tuple_T_T_int = tuple<T, T, int>;//第三个类型只能是int

int main() {

	tuple_three_T<int> tup1;//这里的tup1类型是tuple<int, int, int>
	tuple_T_T_int<string> tup2;//这里的tup2类型是tuple<string, string, int>

	return 0;
}