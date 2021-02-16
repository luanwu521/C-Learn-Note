#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Student {//����һ��ѧ���� �ṩ���������Ĺ��캯��
public://Ϊ�˷������ �Ͷ������public����
	
	string name = "";//����
	string id = "";//ѧ��
	int age = 0;//����
	int height = 0;//���
	
	Student() {};
	//����ʱ��������
	Student(string name_in) : name(name_in) {};
	~Student() {};

	static bool st(const Student& stu1, const Student& stu2) {
		return stu1.height < stu2.height;
		//sort()Ĭ����<���Ƚϴ�С Ҳ���Ǵ�С����
		//����������ĳ� return stu1.height > stu2.height;
		//���ɸı�����˳�� Ҳ���ǴӴ�С
	};

	void print() {
		cout << "Name:" << name << "  "
			<< "Id:" << id << "  "
			<< "Age:" << age << "  "
			<< "Height:" << height << endl;
	};

	bool operator< (const Student& rhs) {//���������<
		//����֪�� �����<�ǽ�������������
		//Ҳ����<�����һ������ �ұ�һ������ һ������
		//�������������涨�����operator ����һ����������ʽ����� ��this����
		//��������������β�ֻ��һ��rhs
		return this->name < rhs.name;
		//��this���ʵ�����ߵĶ���
		//��Ϊ�βε�rhs���ұߵĶ���
	};

};

int main() 
{
	//C++ STL���õ������׾������� �����㷨 ����������
	//���ǽ�һһ����˵��

	//C++�� ��������Ҫ�洢���ݵ�ʱ�� ���ȿ�����STL����
	//STL�����е�vector�������ɱ䳤���� Ҳ�������Ĵ�С�ǿ��Զ�̬�仯��
	//�е�������new�Ķ�̬���� ����vector��ΪSTL��һ������ �ṩ�˺ܶ������㷨
	//Ҳ����˵ vector��һ��������õ�����
	vector<Student> vec_stu;
	for (int i = 0; i < 5; i++) {
		Student stu = Student("stu" + to_string(i));
		vec_stu.push_back(stu);//��������ѧ���������vector��
	}
	
	//vector.size()���Ի�ȡ��ǰ�������ж��ٸ�����
	for (unsigned j = 0; j < vec_stu.size(); j++) {
		//vector֧�ֺܶ���������ͨ����Ĺ���
		//�������±����vector�д洢�Ķ���
		vec_stu[j].id = to_string(j * 1000);//����ѧ����ѧ��
		vec_stu[j].age = j * 10;//��������
		vec_stu[j].height = 180 - j;//�������
		vec_stu[j].print();
	}
	cout << "==========================================================" << endl;
	//STL�ṩ�������ǳ����� ��vector map set��
	//STL�ṩ�������㷨Ҳ�Ǻܳ����� ����ʡ�ºܶ������ӵĹ���
	//��sort()��һ�������㷨 �����������е����ݽ�������
	//sort()Ĭ����ʹ��<�������� Ҳ����������ŵ����ݵ�֧��<��������
	//�����ǿ����ڵ�������������һ���ɵ��ö��� ָ����ν�������
	sort(vec_stu.begin(), vec_stu.end(), Student::st);
	//�������Ǵ�����һ��������st Ҳ�������ǽ�����st������
	//��ΪStudent�ಢû�ж���<���� ����sort()����ֱ��֧������
	//�鿴Student::st() ���Ժ����ԵĿ��� �����Ǹ���Student::height�������
	vector<Student>::iterator it;//����һ��vector�ĵ�����
	for (it = vec_stu.begin(); it != vec_stu.end(); it++) {//��ͷ��ʼ������β
		it->print();//�������ǿ��Կ��� ���Խ�͵�����Խǰ��
	}
	cout << "==========================================================" << endl;
	//����vector����������ʹ���±� Ҳ����ʹ�õ���������
	//������Ҳ��STL��һ���� ���������������д洢������
	//�����㷨��������Ҫ�������������
	//�����sortǰ���������������������� һ����ͷ������ һ����β�������
	//�������������Ϊһ�ַ���ָ�� ��ָ��һ������
	//begin()���Ի�ȡͷ������ ָ�������еĵ�һ������
	//end()���Ի�ȡβ������� ��ָ���������һ������֮���λ�� 
	//��Ȼ β���������ָ���κ�����

	//����˵һ�������Lambda���ʽ�����sort()�ĵ��������� ���������Լ�������
	//����˵sort()�ĵ���������֧�ִ���һ���ɵ��ö��� 
	//Lambda���ʽ�������Ϊһ��С���� ��ô��Ȼ������Ϊsort()�ĵ���������
	auto f1 = [](const Student& stu1, const Student& stu2) -> bool {return stu1.height > stu2.height; };
	//������std::function<bool(const Student&, const Student&)>����auto
	//ʹ��std::functionҪ�ǵ�#include <functional>
	sort(vec_stu.begin(), vec_stu.end(), f1);
	for (it = vec_stu.begin(); it != vec_stu.end(); it++) {//��ͷ��ʼ������β
		it->print();//��ߴӸߵ����� ��Ϊ���Ǹı��˲��Ⱥŷ��� ��<�ĳ���>
	}
	cout << "==========================================================" << endl;


	//����������ڲ�����ɵ��ö��������°����������ֵ����С����������?
	//����˵ �����Զ����������ʱ ��Ĭ��ʹ��<��������
	//��ô��ʱ�����Ǿ�Ҫ��operator���������<
	vec_stu[0].name = "Tdd";
	vec_stu[1].name = "Jiang yilong";
	vec_stu[2].name = "Xiaoming";
	vec_stu[3].name = "Xiaohong";
	vec_stu[4].name = "Xiaowang";
	sort(vec_stu.begin(), vec_stu.end());//��ʱ��û�д������������ Ĭ���Դ洢�����<���������
	for (it = vec_stu.begin(); it != vec_stu.end(); it++) {//��ͷ��ʼ������β
		it->print();//��ʱ�ǰ��ֵ�����������
	}
	cout << "==========================================================" << endl;
	
	return 0;
}
