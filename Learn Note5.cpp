#include <iostream>
using namespace std;

class Book {
public:

	string name = "";//书名
	int count = 0;//数量
	
	Book() {};
	Book(string name_in, int count_in) : name(name_in), count(count_in) {};

	/*
	对于类内实现的运算符重载 我们需要考虑某个运算符可以接受多少个参数
	诸如+-/*等运算符 是可以接受两个参数的
	其中一个参数是以this方式来使用 另一个作为operator的形参
	我们说形如a+b a-b等的形式 this代表着左边的 也就是a 形参代表着右边的 也就是b
	对于只能接受一个参数的运算符 直接使用this即可
	*/


	//当两种书相加时 我们会将他两的数量相加 得到一种新书
	Book operator + (Book& rhs) {
		Book ret_bk = Book();
		ret_bk.count = this->count + rhs.count;
		return ret_bk;
	}

	//当两种书相减时 我们会将他两的数量相减 得到一种新书
	Book operator - (Book& rhs) {
		Book ret_bk = Book();
		ret_bk.count = this->count - rhs.count;
		return ret_bk;
	}
	
};

//类外重载输出运算符
//形参一代表正在操作的流 形参二代表正在执行的对象
//为了保持运算符的一致性 通常会返回形参一 也就是流的引用
ostream& operator<< (ostream& os, const Book& bk) {
	os << "Name:" << bk.name << " Count:" << bk.count;
	return os;
}

//类外重载两书相乘 实际上是将书的数量相乘得到新书
Book operator* (const Book bk1, const Book bk2) {
	Book ret_bk = Book();
	ret_bk.count = bk1.count * bk2.count;
	return ret_bk;
}

int main() 
{
	/*
		内置数据类型支持许多运算符
		现在我们也想让我们自定义的数据类型支持这些运算符
		这样可以在很多情况下方便我们对数据进行操作
		这就需要考虑重载运算符
		我们在类内类外实现一些常见的运算符的重载
	*/
	
	Book book1 = Book("C prime plus", 10);
	Book book2 = Book("数学分析", 5);
	Book book3 = Book("高等代数", 20);
	Book book4 = Book("C++ prime", 15);
	
	cout << book1 << endl;
	cout << book2 << endl;
	cout << book3 << endl;
	cout << book4 << endl;

	cout << (book1 + book2).count << endl;
	cout << (book3 - book1).count << endl;
	cout << (book2 * book4).count << endl;

	return 0;
}