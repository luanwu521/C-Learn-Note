#include <iostream>
#include <string>
#include <memory>
using namespace std;

class living_things {//活体类
private:
	string name = "";
	unsigned age = 0;
protected:
	unsigned life_value = 0;
	unsigned attack_value = 0;
	unsigned defend_value = 0;
public:
	living_things() = default;
	living_things(string name_in) : name(name_in) {};
	virtual ~living_things() = default;

	void set_age(unsigned age_in) { this->age = age_in; };
	unsigned get_age() { return this->age; };
	void set_name(string name_in) { this->name = name_in; };
	string get_name() { return this->name; };

	virtual unsigned calculate_lv() const {
		return attack_value + defend_value;
	};
};
class pet : public living_things {//宠物类
private:
	unsigned hunger_value = 0;//饥饿值
	//每个静态成员变量只存在一个副本 无论实例化了多少个类的对象 静态成员变量都被这些对象共享
	static unsigned count;//声明一个静态成员变量:宠物数量
public:

	//利用父类的构造函数来初始化某些子类从父类继承的成员
	//由于name是living_things的private成员 不能直接初始化name
	//但我们可以通过利用living_things的构造函数间接的初始化子类的name
	pet(string name_in, unsigned life_value_in, unsigned hunger_value_in) : living_things(name_in), hunger_value(hunger_value_in){
		this->life_value = life_value_in;
		this->attack_value = 5;
		this->defend_value = 5;
		count++;//创建一个宠物对象就递增宠物数量
	};
	
	unsigned calculate_lv() const override {
		//同样地 重写威胁力计算函数
		return life_value + attack_value + defend_value - hunger_value;
	}
	
	~pet() {
		count--;//销毁一个宠物对象就递减宠物数量
	}

	//定义一个静态成员函数 这种函数不能访问this指针
	//且只能访问静态成员变量、其他静态成员函数和类外部的其他函数
	static unsigned get_count() {
		return count;//count是静态成员变量 可以被静态成员函数访问
	}
};

unsigned pet::count = 0;//静态成员变量的初始化不能放在类的定义中

int main() {

	pet mode1 = pet("mode1", 10, 3);
	pet mode2 = pet("mode2", 5, 4);
	pet mode3 = pet("mode3", 15, 9);
	cout << "Name:" << mode1.get_name() << " lv:" << mode1.calculate_lv() << endl;
	cout << "Name:" << mode2.get_name() << " lv:" << mode2.calculate_lv() << endl;
	cout << "Name:" << mode3.get_name() << " lv:" << mode3.calculate_lv() << endl;
	cout << "Pet Count:" << pet::get_count() << endl;
	//静态成员同样有权限区分 count是private的 类外是不能访问的
	//想要知道count的值 只能通过类提供的public接口get_count()获取
	//静态成员的访问只需要使用 类名+域运算符(::)+成员名

	cout << "=====================" << endl;

	living_things& mode4 = mode1;
	living_things* ptr1 = &mode2;
	cout << "Name:" << mode4.get_name() << " lv:" << mode4.calculate_lv() << endl;
	cout << "Name:" << ptr1->get_name() << " lv:" << ptr1->calculate_lv() << endl;
	//这里我们使用了living_things类型的引用和指针来管理pet类型的对象
	//通常情况下 指针或引用的类型必须与所管理对象相同
	//但是在继承类的情况下 并不一定要求两者类型相同
	//我们可以用父类类型的指针或引用管理子类对象
	//但这样仅仅可以管理子类对象中从父类继承的那一部分
	//子类独有父类没有的属性是不能通过父类类型的指针或引用进行管理
	shared_ptr<living_things> ptr2 = make_shared<living_things>(mode3);
	cout << "Name:" << ptr2->get_name() << " lv:" << ptr2->calculate_lv() << endl;
	//也可以使用智能指针管理对象 同样遵循上述的特性

	cout << "=====================" << endl;

	return 0;
}