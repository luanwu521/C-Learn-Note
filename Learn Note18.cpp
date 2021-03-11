#include <iostream>
using namespace std;

template <int N> class Fib{
public:
	enum : long{ sum = Fib<N - 1>::sum + Fib<N - 2>::sum };//ģ��ݹ�ʽ
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
	return fib(n - 1) + fib(n - 2);//��ͨ�����ݹ�ʽ
}

int main() {
	
	/*
		�Ƚ�һ��ģ��ĵݹ��ٶȺ���ͨ�����ݹ��ٶ�
		ģ��ݹ���ڱ���ʱ��ɼ��� ����ǰ�Ѿ�֪�����
		��ͨ�ݹ齫������ʱ��ɼ��� ���к��֪�����
	*/

	clock_t start, finish;//��¼��ʼʱ������ʱ��
	const long count = 45;//����쳲��������еڼ���

	start = clock();
	cout << Fib<count>::sum << endl;//ģ��ݹ�
	finish = clock();
	cout << finish - start << endl;//�������ʱ��

	start = clock();
	cout << fib(count) << endl;//��ͨ�����ݹ�
	finish = clock();
	cout << finish - start << endl;//�������ʱ��

	return 0;
}