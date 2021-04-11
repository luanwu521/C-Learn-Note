#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <functional>
using namespace std;

//函数计时器 计算运行f消耗的时间
template <class T, typename... Args>
void js(function<T>& f, Args... args) {
	std::chrono::steady_clock::time_point time_start = std::chrono::steady_clock::now();
	f(args...);
	std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
	cout << "Time(microseconds):" << std::chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << endl;
}

int main() {

	/*
		std::chrono是一个日期时间处理库
	*/

	//以下的seconds minutes等是std::chrono::duration的typedef 表示一个基础时间单位(时钟周期)
	//如seconds是秒 minutes是分钟
	std::chrono::seconds t1(10);
	std::chrono::seconds t2(60);
	std::chrono::seconds t3(t2 - t1);
	cout << t3.count() << endl;
	//count()可以获取时钟周期数 t3定义为t2和t1的时间差 单位为秒
	//时钟周期数是一个时间对象中基础时间单位的个数(时钟周期的个数)

	std::chrono::minutes t4(10);
	std::chrono::seconds t5(60);
	std::chrono::seconds t6(t4 - t5);
	cout << t6.count() << endl;
	//t6定义为t4和t5的差 t4和t5单位不同 会先统一单位后再做差运算
	//count()取决于输出对象的单位 t6调用count() t6单位为秒 则结果应是(10分钟-60秒)的秒结果


	//除了库里已经定义的时间间隔 我们可以自定义时间间隔 以方便在某些特殊场景下使用
	typedef std::chrono::duration<long long, std::ratio<1, 10>> time1;
	//模板参数1是对象所接受的形参类型
	//模板参数2是一个模板 参数1作为分子 参数2作为分母 构成的数值表示时钟周期
	//以上表示单位1/10秒
	time1 t7(20);//代表20 * 1/10 (秒) 这里的参数类型被限制为long long
	cout << t7.count() << endl;//count()输出决定于具体对象的时钟周期
	auto t8 = t5 - t7;
	//事实上这里的推导规则是:取两者分子的最大公约数 分母的最小公倍数 分别作为新分子和分母
	cout << typeid(t8).name() << endl;//可以详细查看一下t8的单位
	cout << t8.count() << endl;
	
	//可以用duration_cast<>()转换成其他的时钟周期 模板参数是std::chrono::duration
	cout << std::chrono::duration_cast<chrono::seconds>(t8).count() << endl;
	cout << std::chrono::duration_cast<chrono::milliseconds>(t8).count() << endl;
	
	//now()返回一个time_point结构 称之为时间点
	//time_point支持算术运算 并可以将结果传入duration_cast<>()
	std::chrono::steady_clock::time_point time_start = std::chrono::steady_clock::now();
	for (int i = 0; i < 10; i++) cout << i;
	cout << endl;
	std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
	//时间周期(单位)调整为microseconds
	cout << "Time:" << std::chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << endl;
	//steady_clock 无法被调整的时钟 以此可以获取稳定的时间间隔 计时器更应该选择这个
	//system_clock 真实世界时钟 时间值依赖于操作系统 若修改了系统时间 则获取的时间值会受到影响
	//high_resolution_clock 高精度时钟 但实际上是上述两者的别名
	
	//可以看见 上述for循环精度需到microseconds才算得耗时 更浅一级的精度milliseconds都无法计算
	//由此可以利用chrono制作一个高精度的函数计时器js()
	
	//我们可以将一个time_point结构转换成一个ctime中定义的结构time_t
	//这样就可以利用标准库里的一些关于时间的函数进行处理了
	std::chrono::system_clock::time_point time_toc = std::chrono::system_clock::now();
	time_t time_c = std::chrono::system_clock::to_time_t(time_toc);//转换
	cout <<put_time(localtime(&time_c), "%Y-%m-%d %X") << endl;//格式化时间并输出
	//事实上也可以利用from_time_t将time_t转换成time_point
	
	return 0;
}