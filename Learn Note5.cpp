#include <iostream>
using namespace std;

class Book {
public:

	string name = "";//����
	int count = 0;//����
	
	Book() {};
	Book(string name_in, int count_in) : name(name_in), count(count_in) {};

	/*
	��������ʵ�ֵ���������� ������Ҫ����ĳ����������Խ��ܶ��ٸ�����
	����+-/*������� �ǿ��Խ�������������
	����һ����������this��ʽ��ʹ�� ��һ����Ϊoperator���β�
	����˵����a+b a-b�ȵ���ʽ this��������ߵ� Ҳ����a �βδ������ұߵ� Ҳ����b
	����ֻ�ܽ���һ������������� ֱ��ʹ��this����
	*/


	//�����������ʱ ���ǻὫ������������� �õ�һ������
	Book operator + (Book& rhs) {
		Book ret_bk = Book();
		ret_bk.count = this->count + rhs.count;
		return ret_bk;
	}

	//�����������ʱ ���ǻὫ������������� �õ�һ������
	Book operator - (Book& rhs) {
		Book ret_bk = Book();
		ret_bk.count = this->count - rhs.count;
		return ret_bk;
	}
	
};

//����������������
//�β�һ�������ڲ������� �βζ���������ִ�еĶ���
//Ϊ�˱����������һ���� ͨ���᷵���β�һ Ҳ������������
ostream& operator<< (ostream& os, const Book& bk) {
	os << "Name:" << bk.name << " Count:" << bk.count;
	return os;
}

//��������������� ʵ�����ǽ����������˵õ�����
Book operator* (const Book bk1, const Book bk2) {
	Book ret_bk = Book();
	ret_bk.count = bk1.count * bk2.count;
	return ret_bk;
}

int main() 
{
	/*
		������������֧����������
		��������Ҳ���������Զ������������֧����Щ�����
		���������ںܶ�����·������Ƕ����ݽ��в���
		�����Ҫ�������������
		��������������ʵ��һЩ�����������������
	*/
	
	Book book1 = Book("C prime plus", 10);
	Book book2 = Book("��ѧ����", 5);
	Book book3 = Book("�ߵȴ���", 20);
	Book book4 = Book("C++ prime", 15);
	
	cout << book1 << endl;
	cout << book2 << endl;
	cout << book3 << endl;
	cout << book4 << endl;

	cout << (book1 + book2).count << endl;
	cout << (book3 - book1).count << endl;
	cout << (book2 * book4).count << endl;

	return 0;
}