#include <iostream>
using namespace std;

//���岻�޶��������ö������ ����������Ϊ�޷�������
enum fruit : unsigned {
	APPLE = 0u,
	BANANA = 1u,
	ORANGE = 2u
};

//�����޶��������ö������
enum class animal : unsigned {//��������Ϊ�޷�������
	PIG = 0u,//u�Ǻ�׺ ���޷�������
	DOG = 1u,
	MONKEY = 2u
};

int main() {
	/*
		ö����һϵ�����γ����ļ��� 
		����һ��ö�پ��Ƕ���һ��������
		����ͨ���Ὣһ�������⺬����������ݹ�����һ��ö������
	*/

	fruit demo1 = APPLE;
	//δ�޶������� ��ֱ�ӷ���ö���е���APPLE ����Ҫʹ���������
	//fruit��һ��ö������ �ɴ˶�����һ������Ϊfruit��demo1���� ֵΪAPPLE
	int i = demo1;//δ�޶��������ö�����Ϳ�����ʽת����int����
	cout << "demo1:" << demo1 << endl;
	cout << "i:" << i << endl;

	//�޶��������� ��Ҫʹ�����������ָ��ʹ�õ�ö����
	animal demo2 = animal::DOG;
	animal demo3 = animal::MONKEY;
	//int j = demo2;
	//�޶��������ö�ٲ�����ʽת����int
	
	return 0;
}