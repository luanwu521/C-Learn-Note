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
		C++�ж����˶����� ���г��õ��б�׼������������ļ������ַ�����
		�ڿ���̨�����¾������ñ�׼����������������� ��cin cout
		��C�� ��д�ļ����ǻ�Ƶ�����õ�ָ��
		����C++�� �ṩ��һ���µĶ�д�ļ��ķ�ʽ ���������ļ���
		���� C++Ҳ�ṩ��һЩ�����ַ����ķ�ʽ �������ַ�����
		�ļ������ַ������������ ���ǿ��������ַ������������ļ��д洢������
		#include <fstream> �ļ������ͷ�ļ�
		#include <sstream> �ַ��������ͷ�ļ�
	*/

	vector<Book> vec_bk;
	string str = "";
	string file = "Other file/test2.txt";
	
	//������һ���洢��ͼ����Ϣ���ļ�test2.txt
	//���������ļ�����ȡ����洢����Ϣ
	//���ȴ���һ���ļ������� Ϊ���캯�������ļ�·���ʹ򿪷�ʽ
	//����Ĵ򿪷�ʽfstream::in�������ǽ�Ҫ���ļ����ж�����
	fstream fp1(file, fstream::in);
	
	//ʹ��getline()��ȡ���е�һ�� �����е����ݴ�ŵ�һ��string��
	//�����whileѭ�����Խ����������ж�ȡ��
	while (getline(fp1, str)) {
		stringstream op(str);
		//��string�����е����ݷŵ��ַ�������
		//���ﹹ����һ���ַ�����op
		Book bk = Book();
		op >> bk.name >> bk.count;//��ȡ���е����� ���Կհ��ַ�
		vec_bk.push_back(bk);
	}
	fp1.close();//�ļ�������͹ر�

	vector<Book>::iterator it;
	for (it = vec_bk.begin(); it != vec_bk.end(); it++) {
		cout << *it << endl;
	}
	
	//���˾������ļ������ַ�����ʵ���˶�ȡ�ļ����ݲ��洢�������Ĺ���
	//��Ȼ ���ǻ����������ļ������ļ�ʵʩд����
	//ͬ���ȴ�һ���ļ� �򿪷�ʽ����Ϊfstream::app
	//fstream::app��ʾ��Ҫ�Ե�ǰ�ļ�����д���� ���Ҳ������ԭ�����ڵ�����
	//���ѡ��fstream::out��ʽ���ļ� ��ô������յ�ǰ�ļ�����������
	fstream fp2(file, fstream::app);
	fp2 << "new_book1" << " " << 10 << endl;
	fp2 << "new_book2" << " " << 5 << endl;
	fp2 << "new_book3" << " " << 27 << endl;
	//�������Ǿ͸��ļ�д�����������������
	//������ͨ�����������>> <<�ͺ���getline()
	cout << "��������д�����" << endl;

	return 0;
}