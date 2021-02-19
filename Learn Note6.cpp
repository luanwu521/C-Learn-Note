#include <iostream>
#include <random>
#include <ctime>
using namespace std;

int main() {

	/*
		原C库中的随机数函数rand()局限性比较大
		我们考虑用支持更多功能的C++随机数库来生成随机数
		使用这个随机数标准库 需要确定随机数引擎和分布类型模板
		随机数引擎主要用于生成原始随机数 一般不直接使用原始随机数
		分布类型模板将利用随机数引擎生成指定规则的随机数
	*/

	default_random_engine e = default_random_engine();
	//以编译器默认的随机数引擎实例化一个随机数对象 
	//不同的随机数引擎性能也是不同的
	//随机数引擎的构造函数支持传入一个整数 作为随机数种子
	//若是使用默认的构造函数 那么将使用默认的随机数种子
	for (int i = 0; i < 5; i++) {
		cout << e() << endl;
		//随机数引擎类是一个函数对象类 该调用不接受参数 并将生成随机数
		//生成的随机数的性质由随机数引擎决定
	}
	cout << "Min:" << e.min() << " Max:" << e.max() << endl;
	//类似C库的rand() C++中的随机数引擎也有一个取值范围
	cout << "=====================" << endl;
	
	//我们需要利用引擎生成我们需要的随机数 这就要靠分布类型模板了
	
	uniform_int_distribution<unsigned> u1(0, 100);
	//首先指定一个分布类型uniform_int_distribution：离散均匀分布
	//然后指定生成的随机数的类型：unsigned 无符号整数类型
	//再由构造函数的两个参数确定一个范围从0到100
	
	e.seed(time(nullptr));//设置一个随机数种子
	//time()接受一个指向时间结构的指针 若指针为空 则简单返回时间
	//这个时间是一个特定时刻到现在经过了多少秒

	for (int i = 0; i < 5; i++) {
		cout << u1(e) << endl;
		//分布类型也是一种函数对象类 也可以调用
		//将随机数引擎作为实参传入即可
	}
	cout << "=====================" << endl;

	uniform_real_distribution<double> u2(0, 1);
	//分布类型uniform_real_distribution：连续均匀分布
	//范围从0到1
	e.seed(time(nullptr));
	for (int i = 0; i < 5; i++) {
		cout << u2(e) << endl;
	}

	return 0;
}