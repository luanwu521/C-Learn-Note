#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main() {

	/*
		有一些数据需要进行处理后再输出
		C++中的流提供了些许操作符对输出进行处理
		这样 就可以使用更加全面的流了
		我们用标准输出流来演示
	*/

	//bool值默认的输出方式是0或1 想要输出true或false 可以使用boolalpha
	cout << "default:" << true << " " << false << endl;
	cout << "alpha:" << boolalpha << true << " " << false << endl;
	cout << noboolalpha;//关闭boolalpha 那么bool值将继续按照0/1输出

	//整数值默认情况下以十进制输出 我们可以考虑输出其他进制
	int n = 15;
	cout << showbase;//开启输出的时候显示进制
	cout << "默认十进制:" << n << endl;
	cout << "十六进制:" << hex << n << endl;
	//默认十六进制的字母会以小写输出 可以开启uppercase以更改为大写
	cout << "十六进制大写:" << uppercase << hex << n << endl;
	cout << "八进制:" << oct << n << endl;
	cout << nouppercase << noshowbase;//关闭进制显示和十六进制字母大写

	//stew()设置数据的输出宽度 数据不足宽度默认将会以空白填充
	//left right 用于设置数据的对齐方式
	double m1 = 3.14159;
	double m2 = 2.71828;
	cout << "左对齐:" << setw(10) << left << m1 << endl;
	cout << "左对齐:" << setw(10) << left << m2 << endl;
	cout << "右对齐:" << setw(10) << right << m1 << endl;
	cout << "右对齐:" << setw(10) << right << m2 << endl;
	//setfill()可以改变填充的字符
	cout << "右对齐:" << setfill('*') << setw(10) << right << m2 << setfill(' ') << endl;
	//保留小数点后几位
	cout << "保留小数点后3位:" << fixed << setprecision(3) << m2 << endl;

	//我们说以上格式化输出是对流而言的 不仅是标准输出流 文件流也是一种流
	//那么这些格式化输出对文件流也同样适用
	fstream fp;
	fp.open("test1.txt", fstream::out);//打开一个文件 模式为输出
	fp << showbase << uppercase << hex << n << nouppercase << noshowbase << endl;
	fp << setfill('*') << setw(10) << right << m1 << setfill(' ') << endl;
	fp << setfill('*') << setw(10) << left << m2 << setfill(' ') << endl;
	fp.close();//关闭文件

	//在某些情况下 需要读取流中的空白字符
	//而默认的 流是忽略空白字符的
	char ch;
	cin >> noskipws;//设置可以读取空白字符
	while (cin >> ch) {
		//windows下可以使用ctrl+z表示到达文件末尾(EOF)
		//这样便可置输入流状态为false 从而退出while循环
		cout << ch;
	}
	cin >> skipws;//恢复到默认忽略空白字符的状态

	return 0;
}