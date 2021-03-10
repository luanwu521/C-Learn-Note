#include <iostream>
#include <string>
using namespace std;

class People {
public:
	People() = default;
	People(string name_in, int age_in) : name(name_in), age(age_in) {};
	void print(ostream& os) {
		os << name << " " << age << endl;
	}
	int get_age_more(int t) {
		return age + t;
	}

private:
	string name = "";
	int age = 0;
};

class A {
public:
	int a1 = 666;
};

class B : public A {
public:
	int b1 = 233;
};

int main() {

	People demo1("Jiang", 19);
	People* ptr_1 = &demo1;
	People demo2("Bai", 20);
	People* ptr_2 = &demo2;

	auto f1 = &People::print;//绑定具体成员函数
	(demo1.*f1)(cout);//以对象调用
	(ptr_1->*f1)(cout);//以指针调用

	auto f2 = &People::get_age_more;
	cout << (demo1.*f2)(10) << endl;
	cout << (ptr_1->*f2)(10) << endl;

	using f1_other = void (People::*) (ostream&);//类型别名 抽象出函数结构
	f1_other f3 = &People::print;//绑定具体成员函数
	(demo2.*f3)(cout);
	(ptr_2->*f3)(cout);

	//typeid()获取一个对象的类型 存储在一个type_info的类中 
	//type_info这个类无法被构造 创建它的唯一途径是通过typeid()函数
	//type_info类的精确定义取决于编译器 但至少会提供name()方法 表示类型名的可打印形式
	cout << typeid(f1).name() << endl;
	cout << typeid(f2).name() << endl;
	cout << typeid(f3).name() << endl;

	//在同一条继承链中的类 可以通过dynamic_cast<type*>将某个类型的指针转换成指定的type类型的指针
	B* ptr_b1 = new B();
	A* ptr_a1 = dynamic_cast<A*>(ptr_b1);//在运行时将指向B的指针转换成指向A的指针
	cout << ptr_a1->a1 << endl;
	//此时是无法通过A类型指针访问B的特有成员的 只能访问A、B共有成员
	//cout << ptr_a1->b1 << endl;
	delete ptr_b1;

	return 0;
}