#include <iostream>
#include <windows.h>
using namespace std;

//����һЩ����������ɫ��ö���� �������ʹ�ú����
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
	//windows cmd�ڿ����ȷʵ���ĺ����� ǡ�ɽ��쿴��һƪ����cmd�������Ե�����
	//��ô�ͳ�������win api������һ��������ɫ
	//ʹ��win api������#include <windows.h> 
	//��Ȼֻ����windowsƽ̨������������� ��Linux������ϵͳ��û������
	//��ʵ��Ҳ���Ը������ֱ���ɫ���������� ��ϸ�Ŀ���ȥ���api�ֲ� ��������������ĵ�����
	//https://docs.microsoft.com/zh-cn/windows/console/setconsoletextattribute
	//SetConsoleTextAttribute()��һ�������Ǹ��������йصľ��
	//������GetStdHandle()��ȡ������ 
	//����STD_OUTPUT_HANDLE�����ȡһ����׼����豸�ľ��
	//SetConsoleTextAttribute()�ĵڶ��������Ǻ�����������ص�
	//����ڶ������������������ֵı���ɫ ������ɫ������
	//��ͬʱ�������չʾ��|������������

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::red );
	cout << "���Ǻ�ɫ red" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::yellow | COMMON_LVB_UNDERSCORE);
	cout << "���Ǽ����»��ߵĻ�ɫ yellow" << endl;
	//ע�������������һ����|���ӵ�COMMON_LVB_UNDERSCORE����
	//COMMON_LVB_UNDERSCORE��ʾ�����ּ����»���
	//���Ƶ��������Կ���ͨ�������ĵ��õ�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::green);
	cout << "������ɫ green" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::blue);
	cout << "������ɫ blue" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::gray);
	cout << "���ǻ�ɫ gray" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::purple);
	cout << "������ɫ purple" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::white | BACKGROUND_GREEN);
	cout << "���Ǳ���ɫΪ��ɫ�İ�ɫ white" << endl;

	//��Ĭ�ϵĺ�ɫ������ ���ǿ��԰�������ɫ���óɺ�ɫ�� ��ô�Ϳ�������
	//��˵�����Ӿ��Ͽ����� ����ȷʵ��������Ļ������� ����ѡ�и���ճ����֪����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::black );
	cout << "����һ�β����������� �㲻һ�����õ� ���㸴��ճ����֪����" << endl;
	
	//���ָֻ�Ĭ�ϵİ�ɫ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::white);
	cout << "չʾ����!!" << endl;
	return 0;
}
