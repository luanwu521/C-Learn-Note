#include <iostream>
using namespace std;

class A {
public:
	int a1 = 6;
	int operator() () {
		return a1;
	}
};

class B {
public:
	int b1 = 0;
};

class C : public A, public B{//C��̳�A��B�� ���Ƕ���̳�
public:
	int c1 = 0;
};

class D : public virtual A{//����D��̳�A
public:
	int d1 = 0;
};

class E : public virtual A {//����E��̳�A
public:
	int e1 = 0;
};

class F : public D, public E {
public:
	int f1 = 0;
};

int main() {

	C demo_c1;
	//���Ƶ���̳� ����̳�Ҳ����ʹ�û���ָ�����������
	A* ptr_a1 = &demo_c1;//A��C�Ļ��� ������A��ָ�����������C�����
	B* ptr_b1 = &demo_c1;//B��C�Ļ��� ������B��ָ�����������C�����
	cout << ptr_a1->a1 << endl;
	cout << ptr_b1->b1 << endl;
	//ptr_a1->c1 ���� ��Ϊptr_a1�ľ�̬������A��ָ�� ֻ�ܷ���A�ĳ�Ա
	//ptr_b1->c1 ���� ��Ϊptr_b1�ľ�̬������B��ָ�� ֻ�ܷ���B�ĳ�Ա

	F demo_f1;//����һ��F���͵Ķ���
	//���Կ���Fͬʱ�̳���D��E ��D��Eͬʱ�ּ̳���A ��ô��F�оͻ��������A�Ŀ���
	//Ϊ�˱���������� ���ǻὫA��D��E�ļ̳����ó���̳� �����Ϳ��Ա�֤ ��������½�����A��һ�ݿ���
	cout << demo_f1.a1 << demo_f1.d1 << demo_f1.e1 << demo_f1.f1 << endl;
	//A���ǳ�֮Ϊ����� ������������ڷ�����๹���
	//���찴�������б�����ҵ�˳����� 
	//�Ȱ������˳����һ����Ҫ�̳е��� �ҳ����е��������й��� ���ߵڶ��鹹��������
	//��F�Ĺ���:�Ƚ���A�Ĺ��� ��ΪA������� �ٽ���D�Ĺ��� �ٵ�E�Ĺ��� ���F����Ĺ���

	
	//��һ�����Ŵ�����һ����ʱ��A����
	//�ڶ������Ŵ��������ʱ����Ķ��� 
	//��Ϊ����������A�ĵ��������() ����A�Ķ����Ϊ��һ���ɵ��ö���
	cout << A()() << endl;

	return 0;
}