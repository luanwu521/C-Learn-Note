#include <iostream>
#include <functional>
using namespace std;

int add(int x, int y) { return x + y; }

int main() {

	/*
		std::function<>可以用来包装可调用对象 如重载了()的类 Lambda表达式等
		注意 std::function<>不能包装类成员指针
		std::bind<>将可调用对象和参数绑定在一起
	*/

	//std::placeholders::_X是占位符 调用时会自动将参数替换到占位符所在位置
	//第一个参数对应std::placeholders::_1 第二个参数对应std::placeholders::_2 以此类推
	//这里std::function包装了外部定义的函数add() 函数接受两个int 返回int
	std::function<int(int, int)> fr1 = std::bind(add, std::placeholders::_1, std::placeholders::_2);
	cout << fr1(23, 233) << endl;;

	//std::bind返回一个仿函数类型 可以赋给std::function 也可以直接调用
	cout << std::bind(add, std::placeholders::_1, 10)(30) << endl;
	cout << std::bind(add, 5, std::placeholders::_2)(30, 40) << endl;//30是用不到的
	//这里add()的参数一已经被bind固定为5 参数二会考虑std::placeholders::_2替换 也就是40

	auto fr2 = std::bind(add, std::placeholders::_1, 66);
	cout << fr2(90) << endl;

	//std::function直接包装Lambda 
	std::function<int(int, int)> f2 = [](int x, int y) -> int {return x > y ? x : y; };
	cout << f2(60, 23) << endl;

	//利用std::bind包装Lambda
	std::function<int(int)> f3 = std::bind([](int x, int y) -> int {return x < y ? x : y; }, std::placeholders::_1, 100);
	cout << f3(120) << endl;
	
	return 0;
}