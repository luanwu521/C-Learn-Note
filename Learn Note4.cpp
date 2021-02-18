#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

int main() 
{
	/*
		C++11�ṩ��һ�����ݽṹtuple һ���̶��Ͽ���ȡ���ṹ��Struct
		tupleҲ��һ��ģ�� ����һ��tupleʱ��Ҫָ��ÿ����Ա������
	*/

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	//����һ��cmd��������ɫ �������һЩ
	
	//Լ��tuple������Ա�ֱ��ʾ:���� ���� ���
	tuple<string, int, int> Student("Xiaoming", 19, 175);
	//����ʹ��get<i>(tuple_name) ������tuple�д洢������
	//����i��ʾ����ʱ����ĵڼ������� tuple_name�Ǵ洢tuple�ı�����
	//��ȻgetҲ��һ��ģ�庯��
	cout << "Name:" << get<0>(Student) << endl;
	cout << "Age:" << get<1>(Student) << endl;
	cout << "Height:" << get<2>(Student) << endl;
	cout << "===========================" << endl;

	//������ʹ��tie()��tupleֱ�ӽ�� �������Ա��ȡ������ָ���ĵ�ַ��
	string name;
	int age;
	int height;
	tie(name, age, height) = Student;
	//��Student����Ա������ȡ������ָ���ı�����
	cout << "Name:" << name << endl;
	cout << "Age:" << age << endl;
	cout << "Height:" << height << endl;
	cout << "===========================" << endl;

	//���ǿ��Ǵ���һ��ѧ������
	vector<tuple<string, int, int>> vec_stu;
	//make_tuple()�������ڴ���һ��tupleʵ��
	//����ʹ��forѭ������10��ѧ��
	for (int i = 0; i < 10; i++) {
		vec_stu.push_back(make_tuple("stu" + to_string(i), 18 + i, 170 + i));
	}
	for (int i = 0; i < 10; i++) {
		//����ѧ������ vector�е�ÿһ����Ա����һ��tuple 
		//��vectorÿ����Ա�����Ե���get<>()����ȡ���д洢������
		//���Զ�һ��string����ʹ��c_str()����ת����C�����ַ��� 
		//��Ϊ�������������õ���printf() %s��������string����
		printf("Name:%s  Age:%d  Height:%d \n", get<0>(vec_stu[i]).c_str(), get<1>(vec_stu[i]), get<2>(vec_stu[i]));
	}
	cout << "===========================" << endl;
	
	//����ĳЩ����� ���ǲ������tuple���и�����Ա����Ϣ
	//�����ǲ�֪���������͵�ʱ�� ��û�취���������
	//��������ζ���ĳЩ�������洢tuple����Աֵ��?
	//���ǿ��Կ���ʹ����������ģ�� �õ���Ա���ͻ��Ա����
	//decltype()�����Ʋ���ʽ����������
	typedef decltype(Student) stu_type;
	//��ô���������stu_type��һ����Studentһ����tuple
	int count = tuple_size<stu_type>::value;
	cout << "Count:" << count << endl;
	//ͨ��tuple_size<>::valueģ���ȡ��ǰtuple�ж��ٸ���Ա
	//�鿴��� �����count���Ϊ3 ��ô����Student��3����Ա
	//��ô���ǿ��Կ��Ƕ���3������ �洢������Աֵ
	//���ڸ���ĳ�Ա���� ������ѭ��ʵ������洢����
	tuple_element<0, stu_type>::type v1 = get<0>(Student);
	tuple_element<1, stu_type>::type v2 = get<1>(Student);
	tuple_element<2, stu_type>::type v3 = get<2>(Student);
	//ͨ��tuple_element<>::type��ȡĳ����Ա������
	//�����ͳɹ�������3������v1 v2 v3 �����ӦStudent������Ա
	//ĿǰΪֹ �����ú����Student����Ա�����͵�����ʲô
	cout << v1 << " " << v2 << " " << v3 << endl;
	return 0;
}