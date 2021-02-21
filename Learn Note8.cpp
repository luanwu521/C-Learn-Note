#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Book {
public:
	string name = "";
	int count = 0;

	Book() {};
	Book(string name_in, int count_in) : name(name_in), count(count_in) {};
};
ostream& operator<< (ostream& os, Book bk) {
	os << "Name:" << bk.name << " Count:" << bk.count;
	return os;
}

int main()
{
	/*
		C++中定义了多种流 其中常用的有标准输入输出流、文件流、字符串流
		在控制台环境下经常利用标准输入输出流交互数据 如cin cout
		在C中 读写文件我们会频繁利用到指针
		而在C++中 提供了一种新的读写文件的方式 就是利用文件流
		另外 C++也提供了一些处理字符串的方式 即利用字符串流
		文件流和字符串流密切相关 我们可以利用字符串流来处理文件中存储的内容
		#include <fstream> 文件流相关头文件
		#include <sstream> 字符串流相关头文件
	*/

	vector<Book> vec_bk;
	string str = "";
	string file = "Other file/test2.txt";
	
	//现在有一个存储了图书信息的文件test2.txt
	//我们利用文件流读取里面存储的信息
	//首先创建一个文件流对象 为构造函数传入文件路径和打开方式
	//这里的打开方式fstream::in代表我们将要对文件进行读操作
	fstream fp1(file, fstream::in);
	
	//使用getline()读取流中的一行 将该行的内容存放到一个string中
	//配合上while循环可以将流中所有行读取完
	while (getline(fp1, str)) {
		stringstream op(str);
		//将string对象中的内容放到字符串流中
		//这里构建了一个字符串流op
		Book bk = Book();
		op >> bk.name >> bk.count;//读取流中的内容 忽略空白字符
		vec_bk.push_back(bk);
	}
	fp1.close();//文件流用完就关闭

	vector<Book>::iterator it;
	for (it = vec_bk.begin(); it != vec_bk.end(); it++) {
		cout << *it << endl;
	}
	
	//至此就利用文件流和字符串流实现了读取文件内容并存储到变量的功能
	//当然 我们还可以利用文件流对文件实施写操作
	//同理先打开一个文件 打开方式设置为fstream::app
	//fstream::app表示将要对当前文件进行写操作 并且不会清空原本存在的内容
	//如果选择fstream::out方式打开文件 那么会先清空当前文件的所有内容
	fstream fp2(file, fstream::app);
	fp2 << "new_book1" << " " << 10 << endl;
	fp2 << "new_book2" << " " << 5 << endl;
	fp2 << "new_book3" << " " << 27 << endl;
	//这样我们就给文件写入了三本新书的数据
	//操作流通常利用运算符>> <<和函数getline()
	cout << "新书数据写入完毕" << endl;

	return 0;
}