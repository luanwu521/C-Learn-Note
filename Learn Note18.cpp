#include <iostream>
using namespace std;

template <int N> class Fib{
public:
	enum : long{ sum = Fib<N - 1>::sum + Fib<N - 2>::sum };//模板递归式
};

template <> class Fib<1>{
public:
	enum : long{ sum = 1 };
};

template <> class Fib<2> {
public:
	enum : long{ sum = 1 };
};

long fib(long n) {
	if (n == 1 || n == 2) { return 1; }
	return fib(n - 1) + fib(n - 2);//普通函数递归式
}

int main() {
	
	/*
		比较一下模板的递归速度和普通函数递归速度
		模板递归会在编译时完成计算 运行前已经知道结果
		普通递归将在运行时完成计算 运行后才知道结果
	*/

	clock_t start, finish;//记录开始时间和完成时间
	const long count = 45;//计算斐波那契数列第几项

	start = clock();
	cout << Fib<count>::sum << endl;//模板递归
	finish = clock();
	cout << finish - start << endl;//输出运行时间

	start = clock();
	cout << fib(count) << endl;//普通函数递归
	finish = clock();
	cout << finish - start << endl;//输出运行时间

	return 0;
}