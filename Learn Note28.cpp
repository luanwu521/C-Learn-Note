#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
using namespace std;

#define COUNT 100000000
int pack[COUNT];

//遍历给定区间查找指定目标
void find_s(int target, int begin = 0, int end = COUNT, int which = 0) {
	for (int i = begin; i < end; i++) {
		if (pack[i] == target) { cout << "Get the target in:[" << which << "]" << endl; break;}
	}
}

//计时函数 计算运行f消耗的时间
template <class T, typename... Args>
void js(function<T>& f, Args... args) {
	std::chrono::steady_clock::time_point time_start = std::chrono::steady_clock::now();
	f(args...);
	std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
	cout << "Time(microseconds):" << std::chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << endl;
}

//封装多线程的任务函数 which表示区间序号
void task(int target, int start, int end, int which) {
	function<decltype(find_s)> f1(find_s);
	js(f1, target, start, end, which);
}

int main() {
	
	//存入1亿个元素 区间总长度为1亿
	for (unsigned i = 0; i < COUNT; i++) pack[i] = i;


	//将1亿个元素拆分成10个区间 那么每个区间的元素个数是总元素个数的十分之一 
	//启动10个线程 同时遍历这10个区间 搜索给定的目标
	//比起1个线程遍历1亿长度的区间寻找目标 多线程的寻标方法耗时明显会少很多
	vector<std::thread> vec;
	for (int j = 0; j < 10; j++) {
		vec.push_back(std::thread(task, 99999999, j * 10000000, (j + 1) * 10000000, j));
		//创建一个线程 第一个参数是任务函数 其他参数是任务函数的参数
	}
	vector<std::thread>::iterator it;
	for (it = vec.begin(); it != vec.end(); it++) {
		it->detach();//启动线程
	}

	//单线程遍历1亿长度的区间
	task(99999999, 0, COUNT, 666);

	//在不开优化的情况下 时间消耗差别将近30倍
	//开了O2的优化下 时间消耗差别大概8倍

	return 0;
}