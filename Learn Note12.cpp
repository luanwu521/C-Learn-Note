#include <iostream>
using namespace std;

class A {//����һ������A
	friend class E;//������Ԫ
public:
	int a1;
protected:
	int a2;
private:
	int a3;
};

class B : public A{//B��public��ʽ�̳�A A�еĳ�Ա����Ȩ�޶�����
public:
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
	int f3() {
		//return a3;
		//���ܷ���a3 ��Ϊa3��private��
	}
};

class C : protected A {//C��protected��ʽ�̳�A ��ôA�г���private�ĳ�Ա ������Ա����protected��
public:
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
};

class D : private A {//D��private��ʽ�̳�A ��ôA�����г�Ա��D�ж���private��
public:
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
	
	using A::a2;//�ı�a2����Ȩ�� ��a2��private�ĳ�public
	
	//using A::a3;
	//�޷��ı����Ȩ�� ��Ϊ��D��û��Ȩ�޷���A��a3
	//һ����ֻ�ܸı��Լ���Ȩ�޷��ʵĳ�Ա�ķ���Ȩ��
};

class E : public A {
public:
	//E��A����Ԫ A�е����г�ԱE�����Է���
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
	int f3() {
		return a3;
		//����a3��A����private�� Ҳ���Է���
	}
};

class F : public D {
public:
	//D��a1��a3����private�� ֻ��a2��public�� ����ֻ�ܷ���a2
	int f1() {
		//return a1;
		//a1��A����public�� ������D�оͱ����private
		//a1��D�б��private��ԭ����:D��private��ʽ�̳�A
		//����a1��F�����޷����ʵ� ��ΪF��ֱ�Ӽ̳�D������ֱ�Ӽ̳�A
	}
	int f2() {
		return a2;
		//��D��a2��public�� ���Կ��Է���
	}
	
};

class G : public E {//G��public�̳�E
public:
	int f1() {
		return a1;
	}
	int f2() {
		return a2;
	}
	int f3() {
		//return a3;
		//�޷�����a3 ��Ϊa3��A����private��
		//E���Է���a3����ΪE��A����Ԫ
		//��G����A����Ԫ ���Բ��ܷ���A��private��Ա
		//��Ҳ˵�� ��Ԫ�ǲ��ɼ̳е� 
		//����G�̳���E E��A����Ԫ������G(�̳���E)��Ҳ��A����Ԫ
	}
};

int main()
{

	return 0;
}