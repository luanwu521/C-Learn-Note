#include <iostream>
#include <type_traits>
#include <memory>

using namespace std;

struct any {
	
	any() = default;

	//any的构造函数接受一个任意类型的参数 那么就可以实现将任意类型值赋给any
	//考虑到我们只关心原始数据类型 传入类型可能包含cv限定符 故采用decay去除
	template<class U> 
	any(U&& value_in) : v_ptr(new Storage<typename decay<U>::type>(forward<U>(value_in))){}
	any(any& rhs) : v_ptr(rhs.v_ptr->get_pointer()){}
	any(any&& rhs) noexcept : v_ptr(std::move(rhs.v_ptr)) {}

	template<class U>
	any& operator=(U&& value_in) {
		BasePtr tmp(new Storage<typename decay<U>::type>(forward<U>(value_in)));
		this->v_ptr = std::move(tmp);
		return *this;
	}

	any& operator=(any& rhs) {
		if (v_ptr != rhs.v_ptr) {
			v_ptr = rhs.v_ptr->get_pointer();
		}
		return *this;
	}

	bool operator==(any& rhs) {
		return this->v_ptr == rhs.v_ptr;
	}

	//取值函数 内部将完成指针转换 以便取出存储的信息
	template<class U>
	U& cast() {
		auto vs = dynamic_cast<Storage<U>*>(v_ptr.get());
		return vs->value;
	}

private:
	struct Base;
	//每个any都会管理一个值 实现中会用到类指针
	//为防止内存泄漏 采用智能指针管理类指针
	using BasePtr = unique_ptr<Base>;
	BasePtr v_ptr;
	
	struct Base
	{
		virtual ~Base() {};
		virtual BasePtr get_pointer() = 0;
	};

	template<class T>
	struct Storage : public Base
	{
		T value;//存储的值

		template<class U>
		Storage(U&& value_in) : value(forward<U>(value_in)){}
		
		BasePtr get_pointer() {
			return BasePtr(new Storage<T>(value));
		}

	};

};


int main() {

	/*
		any类是一个只能容纳一个元素的容器 
		它可以擦除类型
		因此可以赋予它任何类型的值
		基本实现思想:利用基类和派生类的指针互相转换
		我们利用一个模板类Storage存储任意类型T的信息
		再构造一个普通基类Base Base不蕴含任何信息 仅作为一个中介
		然后可以将一个Base指针指向Storage对象 即可实现类型擦除
		当需要使用具体值时 利用dynamic_cast<>() 将Base指针转换成Storage指针即可
	*/
	
	any a1 = 25;
	any a2 = "ovo";
	any a3 = 3.1415;

	//取值时类型必须与原来存值时相同 否则将引发异常 因为类型转换失败
	cout << a1.cast<int>() << endl;
	cout << a2.cast<const char*>() << endl;
	cout << a3.cast<double>() << endl;
	
	a3 = "qwq";
	cout << a3.cast<const char*>() << endl;
	any a4(a1);
	cout << a4.cast<int>() << endl;

	cout << "=======================" << endl;

	any t[] = {a1, a2, a3, a4};
	cout << t[0].cast<int>() << endl;
	cout << t[1].cast<const char*>() << endl;
	cout << t[2].cast<const char*>() << endl;
	cout << t[3].cast<int>() << endl;

	cout << "=======================" << endl;

	any* k = new any[4];
	k[0] = a1;
	k[1] = a2;
	k[2] = a3;
	k[3] = a4;
	cout << k[0].cast<int>() << endl;
	cout << k[1].cast<const char*>() << endl;
	cout << k[2].cast<const char*>() << endl;
	cout << k[3].cast<int>() << endl;

	return 0; 
}