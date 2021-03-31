#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;

int f1(int x, int y) {return x + y;}

int main() {

	/*
		type_traits�����ڱ����ڶ��������ͽ��в���
		�����ж����� ת������ �Ƚ����͵�
		������ͨ��::value��ȡ 
		ת���������ͨ��::type��ȡ
	*/

	
	auto f2 = std::bind([](int x, int y) {return x + y; }, std::placeholders::_1, 100);
	cout << "is_function:" << is_function<decltype(f1)>::value << endl;
	cout << "is_function:" << is_function<decltype(f2)>::value << endl;

	int i = 10;
	int* p = &i;
	cout << "is_pointer:" << is_pointer<decltype(p)>::value << endl;
	cout << "is_arithmetic:" << is_arithmetic<decltype(i)>::value << endl;

	cout << "int is_same remove_reference(int&):" << is_same<int, remove_reference<int&>::type>::value << endl;
	cout << "int is_same remove_pointer(int*):" << is_same<int, remove_pointer<int*>::type>::value << endl;
	//decay<T>�������ָ����Ƴ�cv�޶���(const volatile)
	cout << "int is_same decay(const int):" << is_same<int, decay<const int>::type>::value << endl;
	cout << "is_function<decltype(f1)>::value_type is_same decay(const int):" << is_same<is_function<decltype(f1)>::value_type, decay<const int>::type>::value << endl;
	
	//conditional<B, T, U>������Ԫ����� ��BΪtrue ��::typeȡT������ ����ȡU������
	//����type(T).name()�õ�T�ɴ�ӡ�������ı�
	cout << "conditional<true, int, long>::type:" << typeid(conditional<true, int, long>::type).name() << endl;
	cout << "conditional<false, int, long>::type:" << typeid(conditional<false, int, long>::type).name() << endl;
	cout << "conditional<is_same<int, decay<const int>::type>::value, int, long>::type:" << typeid(conditional<is_same<int, decay<const int>::type>::value, int, long>::type).name() << endl;

	//ģ�����ڱ������Ƶ��� �����е����ͻ��ڱ����ھ��� ��ô����ֻ��ʹ�ó���/�������ʽ
	const int j1 = 10;//���峣��
	constexpr int j2 = -10;//���峣�����ʽ
	constexpr bool B1 = j1 > 0;
	constexpr bool B2 = j2 > 0;
	cout << "conditional<B1(j1 > 0), int, long>::type:" << typeid(conditional<B1, int, long>::type).name() << endl;
	cout << "conditional<B2(j2 > 0), int, long>::type:" << typeid(conditional<B2, int, long>::type).name() << endl;
	


	return 0;
}