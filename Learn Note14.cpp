#include <iostream>
#include <tuple>
#include <string>
using namespace std;

template <typename T> class C;//ǰ������ ����C��һ��ģ���� �������������ʶC<T>
template <typename T> class A {
	template <typename X> friend class B;//B����������ʵ������A����Ԫ
	//��������X һ���µ�ģ����� ��ͬ��T Ŀ����ָ��B���͵������� ������Ҫ��B��A������ͬ
	friend class C<T>;//��������T ָ����C�����ͺ�A������һ��ʱ C���ܳ�ΪA����Ԫ ��Ҫǰ������
	friend class D;//D��һ����ͨ�� D��A����Ԫ ����Ҫǰ������
public:
	int a1;
private:
	int a2;
};

template <typename T> class B {
public:
	
};

template <typename T = int> class C {//ΪT����һ��Ĭ��ʵ��
public:
	template <typename X> C(ostream& os, const X& x) { os << x << endl; };
	//ģ�����п��Զ���ģ�庯�� �����캯�������ģ�庯��
};

class D {
public:
	template <typename X> D(ostream& os, const X& x) { os << x << endl; };
	//��ͨ����Ҳ���Զ���ģ�庯�� �����캯�������ģ�庯��
};

//typedef��֧��ģ�����T�� typedef A<T> A2; �����ǲ������
//���ǿ���typedef A<int> A3; ��Tȷ����(������int)�ǿ��Ե� ��Ϊ���Ѿ���ʵ����ģ����
//Ҫ��ʹģ��ӵ�б����ҿ���ʹ��ģ�����T ����ʹ��using
template <typename T> using tuple_three_T = tuple<T, T, T>;
template <typename T> using tuple_T_T_int = tuple<T, T, int>;//����������ֻ����int

int main() {

	tuple_three_T<int> tup1;//�����tup1������tuple<int, int, int>
	tuple_T_T_int<string> tup2;//�����tup2������tuple<string, string, int>
	
	string str = "Hello World";
	//��ָ��ģ��ʵ����ʹ��Ĭ��ģ��ʵ��
	C<> c1(cout, str);
	C<> c2(cout, 233);
	D d(cout, str);
	
	return 0;
}