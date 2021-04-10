#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
using namespace std;

#define COUNT 100000000
int pack[COUNT];

//���������������ָ��Ŀ��
void find_s(int target, int begin = 0, int end = COUNT, int which = 0) {
	for (int i = begin; i < end; i++) {
		if (pack[i] == target) { cout << "Get the target in:[" << which << "]" << endl; break;}
	}
}

//��ʱ���� ��������f���ĵ�ʱ��
template <class T, typename... Args>
void js(function<T>& f, Args... args) {
	std::chrono::steady_clock::time_point time_start = std::chrono::steady_clock::now();
	f(args...);
	std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
	cout << "Time(microseconds):" << std::chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << endl;
}

//��װ���̵߳������� which��ʾ�������
void task(int target, int start, int end, int which) {
	function<decltype(find_s)> f1(find_s);
	js(f1, target, start, end, which);
}

int main() {
	
	//����1�ڸ�Ԫ�� �����ܳ���Ϊ1��
	for (unsigned i = 0; i < COUNT; i++) pack[i] = i;


	//��1�ڸ�Ԫ�ز�ֳ�10������ ��ôÿ�������Ԫ�ظ�������Ԫ�ظ�����ʮ��֮һ 
	//����10���߳� ͬʱ������10������ ����������Ŀ��
	//����1���̱߳���1�ڳ��ȵ�����Ѱ��Ŀ�� ���̵߳�Ѱ�귽����ʱ���Ի��ٺܶ�
	vector<std::thread> vec;
	for (int j = 0; j < 10; j++) {
		vec.push_back(std::thread(task, 99999999, j * 10000000, (j + 1) * 10000000, j));
		//����һ���߳� ��һ�������������� �����������������Ĳ���
	}
	vector<std::thread>::iterator it;
	for (it = vec.begin(); it != vec.end(); it++) {
		it->detach();//�����߳�
	}

	//���̱߳���1�ڳ��ȵ�����
	task(99999999, 0, COUNT, 666);

	//�ڲ����Ż�������� ʱ�����Ĳ�𽫽�30��
	//����O2���Ż��� ʱ�����Ĳ����8��

	return 0;
}