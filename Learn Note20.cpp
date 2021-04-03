#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;

int f1(int x, int y) {return x + y;}

template <typename T>
typename enable_if<is_arithmetic<T>::value>::type test(T t) {
	cout << "t is " << t << endl;//形参为整形和浮点型调用这个函数
}

template <typename T>
typename enable_if<!is_arithmetic<T>::value>::type test(T& t) {
	cout << "t type:" << typeid(t).name() << endl;//形参不为整形和浮点型调用这个函数
}

int main() {

	/*
		type_traits可以在编译期对数据类型进行操作
		包括判断类型 转换类型 比较类型等
		运算结果通过::value获取 
		转换后的类型通过::type获取
	*/

	auto f2 = std::bind([](int x, int y) {return x + y; }, std::placeholders::_1, 100);
	cout << "is_function:" << is_function<decltype(f1)>::value << endl;
	cout << "is_function:" << is_function<decltype(f2)>::value << endl;
	cout << "typeid(f2):" << typeid(f2).name() << endl;

	int i = 10;
	int* p = &i;
	cout << "is_pointer:" << is_pointer<decltype(p)>::value << endl;
	cout << "is_arithmetic:" << is_arithmetic<decltype(i)>::value << endl;

	cout << "int is_same remove_reference(int&):" << is_same<int, remove_reference<int&>::type>::value << endl;
	cout << "int is_same remove_pointer(int*):" << is_same<int, remove_pointer<int*>::type>::value << endl;
	//decay<T>用于添加指针或移除cv限定符(const volatile)
	cout << "int is_same decay(const int):" << is_same<int, decay<const int>::type>::value << endl;
	cout << "is_function<decltype(f1)>::value_type is_same decay(const int):" << is_same<is_function<decltype(f1)>::value_type, decay<const int>::type>::value << endl;
	
	//conditional<B, T, U>类似三元运算符 若B为true 则::type取T的类型 否则取U的类型
	//利用type(T).name()得到T可打印的类型文本
	cout << "conditional<true, int, long>::type:" << typeid(conditional<true, int, long>::type).name() << endl;
	cout << "conditional<false, int, long>::type:" << typeid(conditional<false, int, long>::type).name() << endl;
	cout << "conditional<is_same<int, decay<const int>::type>::value, int, long>::type:" << typeid(conditional<is_same<int, decay<const int>::type>::value, int, long>::type).name() << endl;

	//模板是在编译期推导的 即所有的类型会在编译期决定 那么我们只能使用常量/常量表达式
	const int j1 = 10;//定义常量
	constexpr int j2 = -10;//定义常量表达式
	constexpr bool B1 = j1 > 0;
	constexpr bool B2 = j2 > 0;
	cout << "conditional<B1(j1 > 0), int, long>::type:" << typeid(conditional<B1, int, long>::type).name() << endl;
	cout << "conditional<B2(j2 > 0), int, long>::type:" << typeid(conditional<B2, int, long>::type).name() << endl;
	
	//获取可调用对象的返回值类型
	using f_ptr = double(*) (int);//函数指针 传入一个int 返回double
	using f_ref = long(&) (int);//函数引用 传入一个int 返回long
	cout << typeid(result_of<f_ptr(int)>::type).name() << endl;
	cout << typeid(result_of<f_ref(int)>::type).name() << endl;
	//普通函数类型f1并不是一个可调用对象 需要转换
	cout << typeid(result_of<decltype(f1)* (int, int)>::type).name() << endl;//转换成函数指针
	cout << typeid(result_of<decltype(f1)& (int, int)>::type).name() << endl;//转换成函数引用

	//enable_if<B, A> fun() 仅当B为true时函数fun()才有效 A为函数返回类型 函数fun()没有返回值可以省略A
	test(20);
	test(3.1415);
	test("ovo");

	return 0;
}