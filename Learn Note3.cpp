#include <iostream>
#include <windows.h>
using namespace std;

//定义一些关于文字颜色的枚举量 方便后面使用和理解
enum Color
{
	black = 0,
	dark_blue = 1,
	dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};
int main()
{
	//windows cmd黑框白字确实看的很腻了 恰巧今天看到一篇关于cmd文字属性的文章
	//那么就尝试利用win api来更改一下文字颜色
	//使用win api我们先#include <windows.h> 
	//当然只能在windows平台下运行这个程序 在Linux或其他系统就没法用了
	//事实上也可以更改文字背景色或其他属性 详细的可以去查查api手册 给出这个函数的文档链接
	//https://docs.microsoft.com/zh-cn/windows/console/setconsoletextattribute
	//SetConsoleTextAttribute()第一个参数是跟命令行有关的句柄
	//我们用GetStdHandle()获取这个句柄 
	//传入STD_OUTPUT_HANDLE代表获取一个标准输出设备的句柄
	//SetConsoleTextAttribute()的第二个参数是和文字属性相关的
	//在这第二个参数可以设置文字的背景色 文字颜色等属性
	//想同时多个属性展示用|链接起来即可

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::red );
	cout << "这是红色 red" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::yellow | COMMON_LVB_UNDERSCORE);
	cout << "这是加了下划线的黄色 yellow" << endl;
	//注意我们这里多了一个用|链接的COMMON_LVB_UNDERSCORE属性
	//COMMON_LVB_UNDERSCORE表示给文字加上下划线
	//类似的其他属性可以通过查找文档得到
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::green);
	cout << "这是绿色 green" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::blue);
	cout << "这是蓝色 blue" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::gray);
	cout << "这是灰色 gray" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::purple);
	cout << "这是紫色 purple" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::white | BACKGROUND_GREEN);
	cout << "这是背景色为绿色的白色 white" << endl;

	//在默认的黑色背景下 我们可以把文字颜色设置成黑色的 那么就看不见了
	//虽说这样视觉上看不见 但是确实存在于屏幕的输出上 把它选中复制粘贴就知道了
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::black );
	cout << "这是一段藏起来的文字 你不一定看得到 但你复制粘贴就知道了" << endl;
	
	//文字恢复默认的白色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::white);
	cout << "展示结束!!" << endl;
	return 0;
}
