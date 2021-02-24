#include <iostream>
#include <string>
using namespace std;

class living_things {//活体类
private://只允许当前类访问
	string name = "";//名字
	unsigned age = 0;//年龄
protected://只允许当前类和子类访问
	unsigned life_value = 0;//生命值
	unsigned attack_value = 0;//攻击力
	unsigned defend_value = 0;//防御力
public://没有限制 都可以访问
	living_things() = default;//default表示采用默认的构造函数
	living_things(string name_in) : name(name_in) {};
	virtual ~living_things() = default;//default表示采用默认的析构函数
	//一般可继承类的析构函数都定义成虚函数

	//设置活体的年龄
	void set_age(unsigned age_in) { this->age = age_in; };
	//获取活体的年龄
	unsigned get_age() { return this->age; };
	//设置活体的名字
	void set_name(string name_in) { this->name = name_in; };
	//获取活体的名字
	string get_name() { return this->name; };

	//计算该活体的威胁力
	//不同活体的威胁力不同 也就是威胁力大小与类别有关 所以定义成虚函数
	//因为我们希望每个继承于活体类的子类可以重写这个威胁力计算函数
	virtual unsigned calculate_lv() const {
		return attack_value + defend_value;
	};
};

class people : public living_things {//人类 继承于 活体类
public:
	
	people(string name_in, unsigned life_value_in) { 
		this->set_name(name_in); 
		//不能直接访问name成员变量 因为它是private的
		//但是可以访问set_name()成员函数 因为它是public的
		this->life_value = life_value_in;
		this->attack_value = 10;
		this->defend_value = 5;
		//people继承于living_things 即people是living_things的子类
		//那么people可以访问living_things的public protected成员
	};
	
	//重写了威胁力计算函数
	//函数后面的const表示 该类的this指针是const的
	//也就是说 类内的成员值都不允许被修改
	//override表示希望编译器强制检查该函数有没有被重写
	unsigned calculate_lv() const override{
		return life_value + attack_value + defend_value;
	};
};

int main() 
{
	living_things mode1 = living_things("mode1");
	people mode2 = people("mode2", 10);
	people mode3 = people("mode3", 20);
	cout << "Name:" << mode1.get_name() << " lv:" << mode1.calculate_lv() << endl;
	cout << "Name:" << mode2.get_name() << " lv:" << mode2.calculate_lv() << endl;
	cout << "Name:" << mode3.get_name() << " lv:" << mode3.calculate_lv() << endl;
	//get_name() 和 calculate_lv() 都是public的 可以在类外访问
	
	return 0;
}
