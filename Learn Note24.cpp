#include <iostream>
#include <type_traits>
#include <memory>
using namespace std;

struct any {
	
	any() = default;

	//any�Ĺ��캯������һ���������͵Ĳ��� ��ô�Ϳ���ʵ�ֽ���������ֵ����any
	//���ǵ�����ֻ����ԭʼ�������� �������Ϳ��ܰ���cv�޶��� �ʲ���decayȥ��
	template<class U> 
	any(U&& value_in) : v_ptr(new Storage<typename decay<U>::type>(forward<U>(value_in))) {}

	//ȡֵ���� �ڲ������ָ��ת�� �Ա�ȡ���洢����Ϣ
	template<class U>
	U& cast() {
		auto vs = dynamic_cast<Storage<U>*>(v_ptr.get());
		return vs->value;
	}

private:
	struct Base;
	//ÿ��any�������һ��ֵ ʵ���л��õ���ָ��
	//Ϊ��ֹ�ڴ�й© ��������ָ�������ָ��
	using BasePtr = unique_ptr<Base>;
	BasePtr v_ptr;

	struct Base
	{
		virtual ~Base() {};
		
	};

	template<class T>
	struct Storage : public Base
	{
		T value;//�洢��ֵ

		template<class U>
		Storage(U&& value_in) : value(forward<U>(value_in)){}
		
	};

};

int main() {

	/*
		any����һ��ֻ������һ��Ԫ�ص����� 
		�����Բ�������
		��˿��Ը������κ����͵�ֵ
		����ʵ��˼��:���û�����������ָ�뻥��ת��
		��������һ��ģ����Storage�洢��������T����Ϣ
		�ٹ���һ����ͨ����Base Base���̺��κ���Ϣ ����Ϊһ���н�
		Ȼ����Խ�һ��Baseָ��ָ��Storage���� ����ʵ�����Ͳ���
		����Ҫʹ�þ���ֵʱ ����dynamic_cast<>() ��Baseָ��ת����Storageָ�뼴��
	*/
	
	any a1 = 10;
	any a2 = "ovo";
	any a3 = 3.1415;

	//ȡֵʱ���ͱ�����ԭ����ֵʱ��ͬ ���������쳣 ��Ϊ����ת��ʧ��
	cout << a1.cast<int>() << endl;
	cout << a2.cast<const char*>() << endl;
	cout << a3.cast<double>() << endl;
	
	a3 = "qwq";
	cout << a3.cast<const char*>() << endl;

	return 0;
}