#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main() {

	/*
		��һЩ������Ҫ���д���������
		C++�е����ṩ��Щ���������������д���
		���� �Ϳ���ʹ�ø���ȫ�������
		�����ñ�׼���������ʾ
	*/

	//boolֵĬ�ϵ������ʽ��0��1 ��Ҫ���true��false ����ʹ��boolalpha
	cout << "default:" << true << " " << false << endl;
	cout << "alpha:" << boolalpha << true << " " << false << endl;
	cout << noboolalpha;//�ر�boolalpha ��ôboolֵ����������0/1���

	//����ֵĬ���������ʮ������� ���ǿ��Կ��������������
	int n = 15;
	cout << showbase;//���������ʱ����ʾ����
	cout << "Ĭ��ʮ����:" << n << endl;
	cout << "ʮ������:" << hex << n << endl;
	//Ĭ��ʮ�����Ƶ���ĸ����Сд��� ���Կ���uppercase�Ը���Ϊ��д
	cout << "ʮ�����ƴ�д:" << uppercase << hex << n << endl;
	cout << "�˽���:" << oct << n << endl;
	cout << nouppercase << noshowbase;//�رս�����ʾ��ʮ��������ĸ��д

	//stew()�������ݵ������� ���ݲ�����Ĭ�Ͻ����Կհ����
	//left right �����������ݵĶ��뷽ʽ
	double m1 = 3.14159;
	double m2 = 2.71828;
	cout << "�����:" << setw(10) << left << m1 << endl;
	cout << "�����:" << setw(10) << left << m2 << endl;
	cout << "�Ҷ���:" << setw(10) << right << m1 << endl;
	cout << "�Ҷ���:" << setw(10) << right << m2 << endl;
	//setfill()���Ըı������ַ�
	cout << "�Ҷ���:" << setfill('*') << setw(10) << right << m2 << setfill(' ') << endl;
	//����С�����λ
	cout << "����С�����3λ:" << fixed << setprecision(3) << m2 << endl;

	//����˵���ϸ�ʽ������Ƕ������Ե� �����Ǳ�׼����� �ļ���Ҳ��һ����
	//��ô��Щ��ʽ��������ļ���Ҳͬ������
	fstream fp;
	fp.open("test1.txt", fstream::out);//��һ���ļ� ģʽΪ���
	fp << showbase << uppercase << hex << n << nouppercase << noshowbase << endl;
	fp << setfill('*') << setw(10) << right << m1 << setfill(' ') << endl;
	fp << setfill('*') << setw(10) << left << m2 << setfill(' ') << endl;
	fp.close();//�ر��ļ�

	//��ĳЩ����� ��Ҫ��ȡ���еĿհ��ַ�
	//��Ĭ�ϵ� ���Ǻ��Կհ��ַ���
	char ch;
	cin >> noskipws;//���ÿ��Զ�ȡ�հ��ַ�
	while (cin >> ch) {
		//windows�¿���ʹ��ctrl+z��ʾ�����ļ�ĩβ(EOF)
		//���������������״̬Ϊfalse �Ӷ��˳�whileѭ��
		cout << ch;
	}
	cin >> skipws;//�ָ���Ĭ�Ϻ��Կհ��ַ���״̬

	return 0;
}