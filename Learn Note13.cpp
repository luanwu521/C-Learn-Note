#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
using namespace std;

//定义一个模板函数 返回两个参数中较小的那个
//模板函数的参数必须是const引用
template <typename T> T test1(const T& T1, const T& T2) {
	return (T1 < T2 ? T1 : T2);//T必须支持运算符<
}

//定义一个模板类
template <typename T> class test2 {
public:
	typedef T value_type;
	typedef typename vector<T>::size_type size_type;
	//typename声明后面跟着的东西是一个类型 
	//因为::可能会导致编译器认为后面跟着的东西是一个类的成员

	test2();
	test2(initializer_list<T> li);
	//接受一个initializer_list<T> 实现用{}来初始化成员

	void push_back(const T& t);
	T& operator[](size_type i);
	
	//在模板类内实现成员函数
	unsigned len() {
		return data->size();
	}

private:
	shared_ptr<vector<T>> data;//利用智能指针管理vector
};

//在模板类外实现成员函数函数 需要通过模板类名来确定成员函数
template <typename T> test2<T>::test2(): data(make_shared<vector<T>>()){}
template <typename T> test2<T>::test2(initializer_list<T> li): data(make_shared<vector<T>>(li)){}
template <typename T> void test2<T>::push_back(const T& t){
	data->push_back(t);
}
template <typename T> T& test2<T>::operator[](size_type i) {
	return (i < data->size() ? (*data)[i] : (*data)[0]);
}

int main() {

	//模板函数可以接受不同类型的实参 实现同样的功能
	cout << test1(2, 3) << endl;//int
	cout << test1(3.14, 2.81) << endl;//double
	cout << test1('S', 'Q') << endl;//char
	
	//因为构造函数接受initializer_list<T> 所以可以用{}来初始化成员
	test2<int> A = { 1, 2, 3, 4, 5 };
	for (unsigned i = 0; i < A.len(); i++) {
		cout << A[i] << " " << ends;
	}
	cout << endl;

	test2<string> B = { "ovo", "qwq", "ouo" };
	B.push_back("qaq");
	for (unsigned i = 0; i < B.len(); i++) {
		cout << B[i] << " " << ends;
	}
	cout << endl;

	return 0;
}