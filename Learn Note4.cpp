#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

int main() 
{
	/*
		C++11提供了一种数据结构tuple 一定程度上可以取代结构体Struct
		tuple也是一种模板 定义一个tuple时需要指出每个成员的类型
	*/

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	//设置一下cmd的文字颜色 看着舒服一些
	
	//约定tuple各个成员分别表示:姓名 年龄 身高
	tuple<string, int, int> Student("Xiaoming", 19, 175);
	//可以使用get<i>(tuple_name) 来访问tuple中存储的数据
	//其中i表示构造时传入的第几个参数 tuple_name是存储tuple的变量名
	//显然get也是一个模板函数
	cout << "Name:" << get<0>(Student) << endl;
	cout << "Age:" << get<1>(Student) << endl;
	cout << "Height:" << get<2>(Student) << endl;
	cout << "===========================" << endl;

	//还可以使用tie()对tuple直接解包 将其各成员提取到我们指定的地址中
	string name;
	int age;
	int height;
	tie(name, age, height) = Student;
	//将Student各成员数据提取到我们指定的变量中
	cout << "Name:" << name << endl;
	cout << "Age:" << age << endl;
	cout << "Height:" << height << endl;
	cout << "===========================" << endl;

	//我们考虑创建一个学生集合 
	vector<tuple<string, int, int>> vec_stu;
	//make_tuple()可以用于创建一个tuple实例
	//考虑使用for循环创建10个学生
	for (int i = 0; i < 10; i++) {
		vec_stu.push_back(make_tuple("stu" + to_string(i), 18 + i, 170 + i));
	}
	for (int i = 0; i < 10; i++) {
		//遍历学生集合 vector中的每一个成员都是一个tuple 
		//对vector每个成员都可以调用get<>()来获取其中存储的数据
		//可以对一个string对象使用c_str()将其转换成C风格的字符串 
		//因为这里的输出函数用的是printf() %s并不接纳string类型
		printf("Name:%s  Age:%d  Height:%d \n", get<0>(vec_stu[i]).c_str(), get<1>(vec_stu[i]), get<2>(vec_stu[i]));
	}
	cout << "===========================" << endl;
	
	return 0;
}