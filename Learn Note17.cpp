#include <iostream>
using namespace std;

//定义不限定作用域的枚举类型 且整形类型为无符号整数
enum fruit : unsigned {
	APPLE = 0u,//u是后缀 表无符号整数
	BANANA = 1u,
	ORANGE = 2u
};

//定义限定作用域的枚举类型
enum class animal : unsigned {//整形类型为无符号整数
	PIG = 0u,
	DOG = 1u,
	MONKEY = 2u
};

int main() {
	/*
		枚举是一系列整形常量的集合 但不代表枚举就一定可以和整形互相转换
		定义一种枚举就是定义一种新类型 将枚举看成一种新类型很重要
		我们通常会将一组有特殊含义的整形数据构建成一个枚举类型
		也就是我们可以赋予某个数字某种意义 如:让0表示苹果或猪
	*/

	fruit demo1 = APPLE;
	//未限定作用域 可直接访问枚举中的量APPLE 不需要使用域运算符
	//fruit是一个枚举类型 由此定义了一个类型为fruit的demo1变量 值为APPLE
	int i = demo1;//未限定作用域的枚举类型可以隐式转换成int类型
	cout << "demo1:" << demo1 << endl;
	cout << "i:" << i << endl;

	//限定了作用域 需要使用域运算符来指定使用的枚举量
	animal demo2 = animal::DOG;
	animal demo3 = animal::MONKEY;
	//int j = demo2;
	//限定作用域的枚举不会隐式转换成int
	
	return 0;
}