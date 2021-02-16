#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Student {//定义一个学生类 提供两个基本的构造函数
public://为了方便调试 就都定义成public的了
	
	string name = "";//姓名
	string id = "";//学号
	int age = 0;//年龄
	int height = 0;//身高
	
	Student() {};
	//构造时设置姓名
	Student(string name_in) : name(name_in) {};
	~Student() {};

	static bool st(const Student& stu1, const Student& stu2) {
		return stu1.height < stu2.height;
		//sort()默认以<来比较大小 也就是从小到大
		//那我们这里改成 return stu1.height > stu2.height;
		//即可改变排序顺序 也就是从大到小
	};

	void print() {
		cout << "Name:" << name << "  "
			<< "Id:" << id << "  "
			<< "Age:" << age << "  "
			<< "Height:" << height << endl;
	};

	bool operator< (const Student& rhs) {//重载运算符<
		//我们知道 运算符<是接受两个参数的
		//也就是<的左边一个对象 右边一个对象 一共两个
		//那我们在类里面定义这个operator 另外一个对象是隐式传入的 用this访问
		//所以我们这里的形参只有一个rhs
		return this->name < rhs.name;
		//用this访问的是左边的对象
		//作为形参的rhs是右边的对象
	};

};

int main() 
{
	//C++ STL常用的三件套就是容器 容器算法 容器迭代器
	//我们将一一举例说明

	//C++中 当我们需要存储数据的时候 优先考虑用STL容器
	//STL容器中的vector可以理解成变长数组 也就是它的大小是可以动态变化的
	//有点类似于new的动态数组 但是vector作为STL的一大容器 提供了很多内置算法
	//也就是说 vector是一个极其好用的数组
	vector<Student> vec_stu;
	for (int i = 0; i < 5; i++) {
		Student stu = Student("stu" + to_string(i));
		vec_stu.push_back(stu);//将创建的学生对象放入vector中
	}
	
	//vector.size()可以获取当前容器中有多少个数据
	for (unsigned j = 0; j < vec_stu.size(); j++) {
		//vector支持很多类似于普通数组的功能
		//可以用下标访问vector中存储的对象
		vec_stu[j].id = to_string(j * 1000);//设置学生的学号
		vec_stu[j].age = j * 10;//设置年龄
		vec_stu[j].height = 180 - j;//设置身高
		vec_stu[j].print();
	}
	cout << "==========================================================" << endl;
	//STL提供的容器非常好用 如vector map set等
	//STL提供的容器算法也是很常见的 可以省下很多造轮子的功夫
	//如sort()是一种容器算法 用来对容器中的数据进行排序
	//sort()默认是使用<进行排序 也就是你所存放的数据得支持<这个运算符
	//且我们可以在第三个参数传入一个可调用对象 指定如何进行排序
	sort(vec_stu.begin(), vec_stu.end(), Student::st);
	//这里我们传入了一个函数名st 也就是我们将根据st来排序
	//因为Student类并没有定义<运算 所以sort()并不直接支持排序
	//查看Student::st() 可以很明显的看出 我们是根据Student::height来排序的
	vector<Student>::iterator it;//定义一个vector的迭代器
	for (it = vec_stu.begin(); it != vec_stu.end(); it++) {//从头开始遍历到尾
		it->print();//这里我们可以看到 身高越低的排在越前面
	}
	cout << "==========================================================" << endl;
	//访问vector不仅仅可以使用下标 也可以使用迭代器访问
	//迭代器也是STL的一部分 常用来访问容器中存储的数据
	//容器算法基本都需要靠迭代器来完成
	//上面的sort前两个参数便是两个迭代器 一个是头迭代器 一个是尾后迭代器
	//迭代器可以理解为一种泛型指针 它指向一个数据
	//begin()可以获取头迭代器 指向容器中的第一个数据
	//end()可以获取尾后迭代器 它指向容器最后一个数据之后的位置 
	//显然 尾后迭代器不指向任何数据

	//下面说一下如何用Lambda表达式来填充sort()的第三个操作 定义我们自己的排序
	//我们说sort()的第三个参数支持传入一个可调用对象 
	//Lambda表达式可以理解为一种小函数 那么自然可以作为sort()的第三个参数
	auto f1 = [](const Student& stu1, const Student& stu2) -> bool {return stu1.height > stu2.height; };
	//可以用std::function<bool(const Student&, const Student&)>代替auto
	//使用std::function要记得#include <functional>
	sort(vec_stu.begin(), vec_stu.end(), f1);
	for (it = vec_stu.begin(); it != vec_stu.end(); it++) {//从头开始遍历到尾
		it->print();//身高从高到低排 因为我们改变了不等号方向 从<改成了>
	}
	cout << "==========================================================" << endl;


	//那我们如何在不定义可调用对象的情况下按照姓名的字典序从小到大排序呢?
	//我们说 当不自定义排序操作时 将默认使用<进行排序
	//那么这时候我们就要用operator重载运算符<
	vec_stu[0].name = "Tdd";
	vec_stu[1].name = "Jiang yilong";
	vec_stu[2].name = "Xiaoming";
	vec_stu[3].name = "Xiaohong";
	vec_stu[4].name = "Xiaowang";
	sort(vec_stu.begin(), vec_stu.end());//此时并没有传入第三个参数 默认以存储对象的<运算符排序
	for (it = vec_stu.begin(); it != vec_stu.end(); it++) {//从头开始遍历到尾
		it->print();//此时是按字典序升序排列
	}
	cout << "==========================================================" << endl;
	
	return 0;
}
