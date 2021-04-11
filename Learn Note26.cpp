#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <functional>
using namespace std;

//������ʱ�� ��������f���ĵ�ʱ��
template <class T, typename... Args>
void js(function<T>& f, Args... args) {
	std::chrono::steady_clock::time_point time_start = std::chrono::steady_clock::now();
	f(args...);
	std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
	cout << "Time(microseconds):" << std::chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << endl;
}

int main() {

	/*
		std::chrono��һ������ʱ�䴦���
	*/

	//���µ�seconds minutes����std::chrono::duration��typedef ��ʾһ������ʱ�䵥λ(ʱ������)
	//��seconds���� minutes�Ƿ���
	std::chrono::seconds t1(10);
	std::chrono::seconds t2(60);
	std::chrono::seconds t3(t2 - t1);
	cout << t3.count() << endl;
	//count()���Ի�ȡʱ�������� t3����Ϊt2��t1��ʱ��� ��λΪ��
	//ʱ����������һ��ʱ������л���ʱ�䵥λ�ĸ���(ʱ�����ڵĸ���)

	std::chrono::minutes t4(10);
	std::chrono::seconds t5(60);
	std::chrono::seconds t6(t4 - t5);
	cout << t6.count() << endl;
	//t6����Ϊt4��t5�Ĳ� t4��t5��λ��ͬ ����ͳһ��λ������������
	//count()ȡ�����������ĵ�λ t6����count() t6��λΪ�� ����Ӧ��(10����-60��)������


	//���˿����Ѿ������ʱ���� ���ǿ����Զ���ʱ���� �Է�����ĳЩ���ⳡ����ʹ��
	typedef std::chrono::duration<long long, std::ratio<1, 10>> time1;
	//ģ�����1�Ƕ��������ܵ��β�����
	//ģ�����2��һ��ģ�� ����1��Ϊ���� ����2��Ϊ��ĸ ���ɵ���ֵ��ʾʱ������
	//���ϱ�ʾ��λ1/10��
	time1 t7(20);//����20 * 1/10 (��) ����Ĳ������ͱ�����Ϊlong long
	cout << t7.count() << endl;//count()��������ھ�������ʱ������
	auto t8 = t5 - t7;
	//��ʵ��������Ƶ�������:ȡ���߷��ӵ����Լ�� ��ĸ����С������ �ֱ���Ϊ�·��Ӻͷ�ĸ
	cout << typeid(t8).name() << endl;//������ϸ�鿴һ��t8�ĵ�λ
	cout << t8.count() << endl;
	
	//������duration_cast<>()ת����������ʱ������ ģ�������std::chrono::duration
	cout << std::chrono::duration_cast<chrono::seconds>(t8).count() << endl;
	cout << std::chrono::duration_cast<chrono::milliseconds>(t8).count() << endl;
	
	//now()����һ��time_point�ṹ ��֮Ϊʱ���
	//time_point֧���������� �����Խ��������duration_cast<>()
	std::chrono::steady_clock::time_point time_start = std::chrono::steady_clock::now();
	for (int i = 0; i < 10; i++) cout << i;
	cout << endl;
	std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
	//ʱ������(��λ)����Ϊmicroseconds
	cout << "Time:" << std::chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << endl;
	//steady_clock �޷���������ʱ�� �Դ˿��Ի�ȡ�ȶ���ʱ���� ��ʱ����Ӧ��ѡ�����
	//system_clock ��ʵ����ʱ�� ʱ��ֵ�����ڲ���ϵͳ ���޸���ϵͳʱ�� ���ȡ��ʱ��ֵ���ܵ�Ӱ��
	//high_resolution_clock �߾���ʱ�� ��ʵ�������������ߵı���
	
	//���Կ��� ����forѭ�������赽microseconds����ú�ʱ ��ǳһ���ľ���milliseconds���޷�����
	//�ɴ˿�������chrono����һ���߾��ȵĺ�����ʱ��js()
	
	//���ǿ��Խ�һ��time_point�ṹת����һ��ctime�ж���Ľṹtime_t
	//�����Ϳ������ñ�׼�����һЩ����ʱ��ĺ������д�����
	std::chrono::system_clock::time_point time_toc = std::chrono::system_clock::now();
	time_t time_c = std::chrono::system_clock::to_time_t(time_toc);//ת��
	cout <<put_time(localtime(&time_c), "%Y-%m-%d %X") << endl;//��ʽ��ʱ�䲢���
	//��ʵ��Ҳ��������from_time_t��time_tת����time_point
	
	return 0;
}