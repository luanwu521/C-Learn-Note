#include <iostream>
#include <type_traits>
#include <tuple>
using namespace std;

template<size_t N = 0, typename Tup>
typename enable_if<N == tuple_size<Tup>::value>::type test(Tup t) {
	cout << "end" << endl;//�ݹ���ֹ���� ��ֹ����:N == tuple_size
	cout << "===============" << endl;
}

template<size_t N = 0, typename Tup>
typename enable_if<N < tuple_size<Tup>::value>::type test(Tup t) {
	cout << get<N>(t) << endl;//�ӵ�0��Ԫ�ؿ�ʼ ���ε�����ȡ
	test<N + 1>(t);//�ݹ����tupleԪ��
}

//�ɱ����ģ�庯��
template<typename... Args>
void run(Args... args) {
	//�������tuple�е�Ԫ�� ����Ԫ�ظ�������
	test(make_tuple(args...));
}

template <typename... Args>
void run2(Args... args) {
	
	initializer_list<int>{([&]() {cout << args << endl; }(), 0)...};
	cout << "===============" << endl;
	//���ö��ű��ʽ������� ������lambda������ Ҳ���Զ���һ������������
	//initializer_list<int>��û��������; ֻ��������ΪӦ�ö��ű��ʽ���б��ʼ���Ĺ���
	//������ص��Ƕ��ű��ʽ����б��ʼ��������� ��ʵ�ϻ�����ͨ����Ҳ�ǿ�����ɵ�
}

//�ɱ����ģ���� ����enum�õ������ڳ���
template <typename All, typename... Args>
struct sum{
	enum {value = sum<All>::value + sum<Args...>::value };//�Եݹ�+�ػ���ʽչ��������
};

//�ػ��汾 չ����ʣ��һ������Ϊֹ
template <typename One>
struct sum <One> {
	enum { value = sizeof(One)};//�ݹ���ֹ����
};


int main() {

	string str{ "qwq" };
	run(32, "run1", 3.14, str);
	run2(123, 2.33, str, "run2");
	run(); //�ɱ����ģ��Ĳ�����������Ϊ0

	//char1�ֽ� int4�ֽ� double8�ֽ� 
	cout << sum<char, int, double>::value << endl;

	return 0;
}