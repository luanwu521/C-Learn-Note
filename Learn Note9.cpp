#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	
	/*
		流是支持随机访问的 换句话说 就是我们可以操纵流的任意位置
		我们总会遇到一些情况 如修改文件中的某一行数据 其他内容不变
		那么我们需要定位到这一行 只对这一行操作
		这就需要应用到流的随机访问
		当然 还可以应用流的随机访问实现一边读一边写的操作
	*/

	//以读写方式打开一个文件 我们实现一个同时读写的操作
	fstream fp("Other file/test3.txt", fstream::in | fstream::app);

	//tellg()用于返回输入流中当前的标记位置
	auto end_mark = fp.tellg();
	//因为要同时写文件 所以文件的末尾是一直在变的
	//所以要记录原数据的末尾标记

	//seekg()用于重新定位输入流中的标记位置
	fp.seekg(0, fstream::beg);
	//这里是定位到距离文件首长度为0的位置 也就是文件首
	
	size_t cnt = 0;//用于记录读取的字数
	string line = "";//用于记录读取的每一行

	while (fp && getline(fp, line) && fp.tellg() != end_mark) {
		//循环条件:流状态正常 可以成功读取一行 文件没有读到原数据的末尾标记
		//既然读取了一行 那么就可以记录读取的字数了
		cnt += line.size() + 1;//最后还有一个不可见的换行符 也要算上
		auto mark = fp.tellg();//记录读取一行之后现在的位置
		fp.seekp(0, fstream::end);
		//将写标记定位到距离文件尾长度为0的位置 也就是文件尾
		fp << cnt;//写入数据
		if (mark != end_mark) {
			fp << " ";
		}
		fp.seekg(mark);//写入数据完后恢复之前读的位置继续读
	}
	fp.seekg(0, fstream::end);
	fp << "\n";//实现所有操作后 在文件最后换行

	return 0;
}