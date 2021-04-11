#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <mutex>
#include <map>
using namespace std;

#define COUNT 100000000//总量
#define TARGET 99999999//目标
int pack[COUNT];//存储数据的数组
std::atomic<bool> is_find = false;//是否已经找到
map<int, chrono::microseconds> map_time;//存放线程的运行时间
mutex g_lock;//线程锁

//遍历给定区间查找指定目标
int find_s(int target, int begin = 0, int end = COUNT, int which = 0) {
	for (int i = begin; i < end && !is_find; i++) {
		//若有其他线程找到目标了 这个线程也不用继续寻找了
		if (pack[i] == target) { cout << "Get the target in:[" << which << "]" << endl; is_find = true; break; }
	}
	return which;
}

//计时函数 计算运行f消耗的时间
template <class T, typename... Args>
void js(function<T> f, Args... args) {

	std::chrono::steady_clock::time_point time_start = std::chrono::steady_clock::now();
	int w = f(args...);
	std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
	
	//map_time是共享数据 访问之前先上锁
	lock_guard<mutex> locker(g_lock);//lock_guard利用自动管理mutex
	map_time[w] = std::chrono::duration_cast<chrono::microseconds>(time_end - time_start);
}

//封装多线程的任务函数 which表示区间序号
void task(int target, int start, int end, int which) {
	js(function<decltype(find_s)>(find_s), target, start, end, which);
}

int main() {
	
	//存入1亿个元素 区间总长度为1亿
	for (unsigned i = 0; i < COUNT; i++) pack[i] = i;

	//将1亿个元素拆分成10个区间 那么每个区间的元素个数是总元素个数的十分之一 
	//启动10个线程 同时遍历这10个区间 搜索给定的目标
	//比起1个线程遍历1亿长度的区间寻找目标 多线程的寻标方法耗时明显会少很多
	vector<std::thread> vec_thread;
	for (int j = 0; j < 10; j++) {
		vec_thread.push_back(std::thread(task, TARGET, j * 10000000, (j + 1) * 10000000, j));
		//创建一个线程 第一个参数是任务函数 其他参数是任务函数的参数
	}
	vector<std::thread>::iterator it;
	for (it = vec_thread.begin(); it != vec_thread.end(); it++) {
		it->detach();//启动线程
	}

	//阻塞主线程 直到找到目标为止
	while (!is_find) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	auto it2 = map_time.begin();
	for (; it2 != map_time.end(); it2++) {
		cout << "Time[" << it2->first << "]:" << it2->second.count() << endl;
	}

	//单线程遍历1亿长度的区间
	is_find = false;
	task(TARGET, 0, COUNT, 666);
	cout << "Time[" << 666 << "]:" << map_time[666].count() << endl;
	
	//在不开优化的情况下 时间消耗差别将近30倍
	//开了O2的优化下 时间消耗差别大概8倍

	return 0;
}