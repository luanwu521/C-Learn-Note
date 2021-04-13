#include <iostream>
#include <functional>
using namespace std;

template <class T>
struct function_traits;

template<class Ret, class... Args>
struct function_traits<Ret(Args...)> {//ֻ֧����ͨ�������ػ��汾

	enum{arg_size = sizeof...(Args) };//��������
	using function_signed = Ret(Args...);//����ǩ��
	using retur_type = Ret;//����ֵ����
	using function_pointer = Ret(*)(Args...);//����ָ��
	using std_function_type = std::function<function_signed>;//std::function����

	template<size_t N>
	using arg_type = typename std::tuple_element<N, std::tuple<Args...>>::type;
	//��������

};

template<class Ret, class... Args>
struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)>{
	//֧�ֺ���ָ����ػ��汾
	//���ػ��汾����Ret(*)(Args...)����
	//�ػ�������ɲ���ƥ�� ����ʵ��λ��function_traits<Ret(Args...)>
	//ͨ���̳�ʵ���ػ��汾����ȡ
};

template<class Ret, class... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)> {
	//֧��std::function���ػ��汾
	//���ػ��汾����std::function<Ret(Args...)>����
};

double add(double x, double y) { return x + y; }

int main() {

	cout << "add function_signed:" << typeid(function_traits<decltype(add)>::function_signed).name() << endl;

	function_traits<decltype(add)>::std_function_type f(add);
	cout << "add Run result:" << f(13, 17) << endl;

	cout << "add std_function_type:" << typeid(function_traits<decltype(add)>::std_function_type).name() << endl;
	cout << "add arg_type<0>:" << typeid(function_traits<decltype(add)>::arg_type<0>).name() << endl;
	cout << "add arg_type<1>:" << typeid(function_traits<decltype(add)>::arg_type<1>).name() << endl;
	cout << "add return_type:" << typeid(function_traits<decltype(add)>::retur_type).name() << endl;
	cout << "add arg_size:" << function_traits<decltype(add)>::arg_size << endl;

	std::function<void(string, int)> f2 = [](string str, int i) {};//lambda�󶨵�std::function
	
	cout << "f2 function_signed:" << typeid(function_traits<decltype(f2)>::function_signed).name() << endl;
	cout << "f2 arg_type<0>:" << typeid(function_traits<decltype(f2)>::arg_type<0>).name() << endl;
	cout << "f2 arg_type<1>:" << typeid(function_traits<decltype(f2)>::arg_type<1>).name() << endl;
	cout << "f2 return_type:" << typeid(function_traits<decltype(f2)>::retur_type).name() << endl;
	cout << "f2 arg_size:" << function_traits<decltype(f2)>::arg_size << endl;


	return 0;
}