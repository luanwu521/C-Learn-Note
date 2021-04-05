#include <iostream>
#include <functional>
using namespace std;

int add(int x, int y) { return x + y; }

int main() {

	/*
		std::function<>����������װ�ɵ��ö��� ��������()���� Lambda���ʽ��
		std::function<>���ܰ�װ���Աָ��
		std::function<>��ģ�������һ������ǩ�� ��:int(int, int) ��Ϊ:��������int ����int
		std::bind<>���ɵ��ö���Ͳ�������һ��
	*/

	//std::placeholders::_X��ռλ�� ����ʱ���Զ��������滻��ռλ������λ��
	//��һ��������Ӧstd::placeholders::_1 �ڶ���������Ӧstd::placeholders::_2 �Դ�����
	//����std::function��װ���ⲿ����ĺ���add() ������������int ����int
	std::function<int(int, int)> fr1 = std::bind(add, std::placeholders::_1, std::placeholders::_2);
	cout << fr1(23, 233) << endl;;

	//std::bind����һ���º������� ���Ը���std::function Ҳ����ֱ�ӵ���
	cout << std::bind(add, std::placeholders::_1, 10)(30) << endl;
	cout << std::bind(add, 5, std::placeholders::_2)(30, 40) << endl;//30���ò�����
	//����add()�Ĳ���һ�Ѿ���std::bind�̶�Ϊ5 �������ῼ��std::placeholders::_2�滻 Ҳ����40
	 
	auto fr2 = std::bind(add, std::placeholders::_1, 66);
	cout << fr2(90) << endl;

	//std::functionֱ�Ӱ�װLambda 
	std::function<int(int, int)> f2 = [](int x, int y) -> int {return x > y ? x : y; };
	cout << f2(60, 23) << endl;

	//����std::bind��װLambda
	std::function<int(int)> f3 = std::bind([](int x, int y) -> int {return x < y ? x : y; }, std::placeholders::_1, 100);
	cout << f3(120) << endl;
	//�������ǩ������Ϊstd::bind�н���std::placeholders::_1 �ڶ����������̶�����Ϊ100
	//������ʵ�Ͻ�����һ������ �ҷ��ش��������100�е�ĳһ�� ����:����һ��int ����int ��int(int)
	

	//���ú���ָ���ʼ��std::function
	//PTR��һ������ǩ�� ָ���������int������int�ĺ���
	using PTR = int(int, int);
	PTR* p = add;//add()����������PTR ��ô��Ͷ�����һ������ָ��
	std::function<PTR> f4(p);//����p��ʼ��std::function
	cout << f4(123, 456) << endl;

	return 0;
}