#include <iostream>
#include <tuple>
using namespace std;

namespace tuple_helper {

	template<class T, class U>
	typename std::enable_if<std::is_convertible<T, U>::value || std::is_convertible<U, T>::value, bool>::type
	compare(T lhs, U rhs) {
		return lhs == rhs;
		//利用enable_if和is_convertible确保两种类型的对象可以相互转换 从而可以进行比较
	}

	bool compare(...) {
		return false;//对任何无法比较的两种类型 直接返回false
	}

	//根据值查找索引 N为tuple中元素的个数 T为待查找值的类型 Args...为tuple的参数
	template<int N, class T, class... Args>
	struct find_index
	{
		static int call(std::tuple<Args...>& tp, T&& value) {
			//递归+特化遍历tuple各元素
			return(tuple_helper::compare(std::get<N - 1>(tp), value) ? N - 1 : find_index<N - 1, T, Args...>::call(tp, std::forward<T>(value)));
		}
	};

	template<class T, class... Args>
	struct find_index<1, T, Args...>
	{
		//递归终止 找不到指定值返回-1
		static int call(std::tuple<Args...>& tp, T&& value) {
			return tuple_helper::compare(std::get<0>(tp), value) ? 0 : -1;
		}
		
	};
}

//值查索引辅助函数
template<class T, class... Args>
int find_index(std::tuple<Args...>& tp, T&& value) {
	//借助sizeof...()获取tuple元素个数
	return tuple_helper::find_index<sizeof...(Args), T, Args...>::call(tp, std::forward<T>(value));
}


int main() {
	
	/*
		tuple_helper是一个tuple辅助工具
		封装了一些tuple的常见操作 如:遍历 根据值获取索引等
		该实现基于变参模板 模板推导在编译期执行 这样便可优化运行时间
	*/

	//封装过后只需要传入tuple对象和待查值即可
	//优点在于我们不必充分了解某个tuple对象的具体细节 如:参数个数 参数类型等
	std::tuple<int, double, string> tp = std::make_tuple(1, 2.33, "ouo");
	cout << find_index(tp, 2.33) << endl;
	cout << find_index(tp, 666) << endl;//找不到

	return 0;
}