#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Student {//定义一个学生类 提供两个基本的构造函数
public:
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
	};

	void print() {
		cout << "==========================================================" << endl;
		cout << "Name:" << name << "  "
			<< "Id:" << id << "  "
			<< "Age:" << age << "  "
			<< "Height:" << height << endl;
		cout << "==========================================================" << endl;
	}
};

int main() 
{
	//C++中 当我们需要存储数据的时候 优先考虑用vector
	//vector可以理解成变长数组 也就是它的大小是可以动态变化的
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
	
	//STL提供的容器非常好用 如vector map set等
	//STL提供的容器算法也是很常见的 可以省下很多造轮子的功夫
	//如sort()是一种容器算法 用来对容器中的数据进行排序
	//sort()默认是使用<进行排序 也就是你所存放的数据得支持<这个运算符
	//且我们可以在第三个参数传入一个可调用对象 指定如何进行排序
	sort(vec_stu.begin(), vec_stu.end(), Student::st);
	//这里我们传入了一个函数名st 也就是我们将根据st来排序
	//因为Student类并没有定义<运算 所以sort()并不直接支持排序
	//查看Student::st() 可以很明显的看出 我们是根据Student::height来排序的
	vector<Student>::iterator it = vec_stu.begin();//从头开始
	for (; it != vec_stu.end(); it++) {//遍历到尾
		it->print();//这里我们可以看到 身高越低的排在越前面
	}
	//访问vector不仅仅可以使用下标 也可以使用迭代器访问
	//迭代器也是STL的一部分 常用来访问容器中存储的数据
	//容器算法基本都需要靠迭代器来完成
	//上面的sort前两个参数便是两个迭代器 一个是头迭代器 一个是尾后迭代器
	//迭代器可以理解为一种泛型指针 它指向一个数据
	//begin()可以获取头迭代器 指向容器中的第一个数据
	//end()可以获取尾后迭代器 它指向容器最后一个数据之后的位置 
	//显然 尾后迭代器不指向任何数据
	return 0;
}
