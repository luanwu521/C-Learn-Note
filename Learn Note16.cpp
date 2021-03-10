#include <iostream>
#include <string>
using namespace std;

class People {
public:
	People() = default;
	People(string name_in, int age_in) : name(name_in), age(age_in) {};
	void print(ostream& os) {
		os << name << " " << age << endl;
	}
	int get_age_more(int t) {
		return age + t;
	}

private:
	string name = "";
	int age = 0;
};

class A {
public:
	int a1 = 666;
};

class B : public A {
public:
	int b1 = 233;
};

int main() {

	People demo1("Jiang", 19);
	People* ptr_1 = &demo1;
	People demo2("Bai", 20);
	People* ptr_2 = &demo2;

	auto f1 = &People::print;//�󶨾����Ա����
	(demo1.*f1)(cout);//�Զ������
	(ptr_1->*f1)(cout);//��ָ�����

	auto f2 = &People::get_age_more;
	cout << (demo1.*f2)(10) << endl;
	cout << (ptr_1->*f2)(10) << endl;

	using f1_other = void (People::*) (ostream&);//���ͱ��� ����������ṹ
	f1_other f3 = &People::print;//�󶨾����Ա����
	(demo2.*f3)(cout);
	(ptr_2->*f3)(cout);

	//typeid()��ȡһ����������� �洢��һ��type_info������ 
	//type_info������޷������� ��������Ψһ;����ͨ��typeid()����
	//type_info��ľ�ȷ����ȡ���ڱ����� �����ٻ��ṩname()���� ��ʾ�������Ŀɴ�ӡ��ʽ
	cout << typeid(f1).name() << endl;
	cout << typeid(f2).name() << endl;
	cout << typeid(f3).name() << endl;

	//��ͬһ���̳����е��� ����ͨ��dynamic_cast<type*>��ĳ�����͵�ָ��ת����ָ����type���͵�ָ��
	B* ptr_b1 = new B();
	A* ptr_a1 = dynamic_cast<A*>(ptr_b1);//������ʱ��ָ��B��ָ��ת����ָ��A��ָ��
	cout << ptr_a1->a1 << endl;
	//��ʱ���޷�ͨ��A����ָ�����B�����г�Ա�� ֻ�ܷ���A��B���г�Ա
	//cout << ptr_a1->b1 << endl;
	delete ptr_b1;

	return 0;
}