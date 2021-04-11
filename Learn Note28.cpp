#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <mutex>
#include <map>
using namespace std;

#define COUNT 100000000//����
#define TARGET 99999999//Ŀ��
int pack[COUNT];//�洢���ݵ�����
std::atomic<bool> is_find = false;//�Ƿ��Ѿ��ҵ�
map<int, chrono::microseconds> map_time;//����̵߳�����ʱ��
mutex g_lock;//�߳���

//���������������ָ��Ŀ��
int find_s(int target, int begin = 0, int end = COUNT, int which = 0) {
	for (int i = begin; i < end && !is_find; i++) {
		//���������߳��ҵ�Ŀ���� ����߳�Ҳ���ü���Ѱ����
		if (pack[i] == target) { cout << "Get the target in:[" << which << "]" << endl; is_find = true; break; }
	}
	return which;
}

//��ʱ���� ��������f���ĵ�ʱ��
template <class T, typename... Args>
void js(function<T> f, Args... args) {

	std::chrono::steady_clock::time_point time_start = std::chrono::steady_clock::now();
	int w = f(args...);
	std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
	
	//map_time�ǹ������� ����֮ǰ������
	lock_guard<mutex> locker(g_lock);//lock_guard�����Զ�����mutex
	map_time[w] = std::chrono::duration_cast<chrono::microseconds>(time_end - time_start);
}

//��װ���̵߳������� which��ʾ�������
void task(int target, int start, int end, int which) {
	js(function<decltype(find_s)>(find_s), target, start, end, which);
}

int main() {
	
	//����1�ڸ�Ԫ�� �����ܳ���Ϊ1��
	for (unsigned i = 0; i < COUNT; i++) pack[i] = i;

	//��1�ڸ�Ԫ�ز�ֳ�10������ ��ôÿ�������Ԫ�ظ�������Ԫ�ظ�����ʮ��֮һ 
	//����10���߳� ͬʱ������10������ ����������Ŀ��
	//����1���̱߳���1�ڳ��ȵ�����Ѱ��Ŀ�� ���̵߳�Ѱ�귽����ʱ���Ի��ٺܶ�
	vector<std::thread> vec_thread;
	for (int j = 0; j < 10; j++) {
		vec_thread.push_back(std::thread(task, TARGET, j * 10000000, (j + 1) * 10000000, j));
		//����һ���߳� ��һ�������������� �����������������Ĳ���
	}
	vector<std::thread>::iterator it;
	for (it = vec_thread.begin(); it != vec_thread.end(); it++) {
		it->detach();//�����߳�
	}

	//�������߳� ֱ���ҵ�Ŀ��Ϊֹ
	while (!is_find) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	auto it2 = map_time.begin();
	for (; it2 != map_time.end(); it2++) {
		cout << "Time[" << it2->first << "]:" << it2->second.count() << endl;
	}

	//���̱߳���1�ڳ��ȵ�����
	is_find = false;
	task(TARGET, 0, COUNT, 666);
	cout << "Time[" << 666 << "]:" << map_time[666].count() << endl;
	
	//�ڲ����Ż�������� ʱ�����Ĳ�𽫽�30��
	//����O2���Ż��� ʱ�����Ĳ����8��

	return 0;
}