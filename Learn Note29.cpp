#include <iostream>
#include <functional>
using namespace std;

template <class T>
struct function_traits;

template<class Ret, class... Args>
struct function_traits<Ret(Args...)> {//只支持普通函数的特化版本

	enum{arg_size = sizeof...(Args) };//参数个数
	using function_signed = Ret(Args...);//函数签名
	using retur_type = Ret;//返回值类型
	using function_pointer = Ret(*)(Args...);//函数指针
	using std_function_type = std::function<function_signed>;//std::function类型

	template<size_t N>
	using arg_type = typename std::tuple_element<N, std::tuple<Args...>>::type;
	//参数类型

};

template<class Ret, class... Args>
struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)>{
	//支持函数指针的特化版本
	//该特化版本接受Ret(*)(Args...)类型
	//特化用以完成参数匹配 基本实现位于function_traits<Ret(Args...)>
	//通过继承实现特化版本的萃取
};

template<class Ret, class... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)> {
	//支持std::function的特化版本
	//该特化版本接受std::function<Ret(Args...)>类型
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

	std::function<void(string, int)> f2 = [](string str, int i) {};//lambda绑定到std::function
	
	cout << "f2 function_signed:" << typeid(function_traits<decltype(f2)>::function_signed).name() << endl;
	cout << "f2 arg_type<0>:" << typeid(function_traits<decltype(f2)>::arg_type<0>).name() << endl;
	cout << "f2 arg_type<1>:" << typeid(function_traits<decltype(f2)>::arg_type<1>).name() << endl;
	cout << "f2 return_type:" << typeid(function_traits<decltype(f2)>::retur_type).name() << endl;
	cout << "f2 arg_size:" << function_traits<decltype(f2)>::arg_size << endl;


	return 0;
}