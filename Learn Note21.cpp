#include <iostream>
#include <type_traits>
#include <tuple>
using namespace std;

template<size_t N = 0, typename Tup>
typename enable_if<N == tuple_size<Tup>::value>::type test(Tup t) {
	cout << "end" << endl;//递归终止函数 终止条件:N == tuple_size
	cout << "===============" << endl;
}

template<size_t N = 0, typename Tup>
typename enable_if<N < tuple_size<Tup>::value>::type test(Tup t) {
	cout << get<N>(t) << endl;//从第0个元素开始 依次递增获取
	test<N + 1>(t);//递归遍历tuple元素
}

//可变参数模板函数
template<typename... Args>
void run(Args... args) {
	//遍历输出tuple中的元素 其中元素个数不定
	test(make_tuple(args...));
}

template <typename... Args>
void run2(Args... args) {
	
	initializer_list<int>{([&]() {cout << args << endl; }(), 0)...};
	cout << "===============" << endl;
	//利用逗号表达式遍历变参 可以用lambda处理变参 也可以定义一个函数处理变参
	//initializer_list<int>并没有其他用途 只是用来作为应用逗号表达式和列表初始化的工具
	//这里的重点是逗号表达式配合列表初始化遍历变参 事实上换成普通数组也是可以完成的
}

//可变参数模板类 利用enum得到编译期常量
template <typename All, typename... Args>
struct sum{
	enum {value = sum<All>::value + sum<Args...>::value };//以递归+特化方式展开参数包
};

//特化版本 展开到剩下一个参数为止
template <typename One>
struct sum <One> {
	enum { value = sizeof(One)};//递归终止条件
};


int main() {

	string str{ "qwq" };
	run(32, "run1", 3.14, str);
	run2(123, 2.33, str, "run2");
	run(); //可变参数模板的参数个数可以为0

	//char1字节 int4字节 double8字节 
	cout << sum<char, int, double>::value << endl;

	return 0;
}