#include <iostream>
#include <type_traits>
#include <memory>

using namespace std;

struct any {
	
	any() = default;

	//any�Ĺ��캯������һ���������͵Ĳ��� ��ô�Ϳ���ʵ�ֽ���������ֵ����any
	//���ǵ�����ֻ����ԭʼ�������� �������Ϳ��ܰ���cv�޶��� �ʲ���decayȥ��
	template<class U> 
	any(U&& value_in) : v_ptr(new Storage<typename decay<U>::type>(forward<U>(value_in))){}
	any(any& rhs) : v_ptr(rhs.v_ptr->get_pointer()){}
	any(any&& rhs) noexcept : v_ptr(std::move(rhs.v_ptr)) {}

	template<class U>
	any& operator=(U&& value_in) {
		BasePtr tmp(new Storage<typename decay<U>::type>(forward<U>(value_in)));
		this->v_ptr = std::move(tmp);
		return *this;
	}

	any& operator=(any& rhs) {
		if (v_ptr != rhs.v_ptr) {
			v_ptr = rhs.v_ptr->get_pointer();
		}
		return *this;
	}

	bool operator==(any& rhs) {
		return this->v_ptr == rhs.v_ptr;
	}

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
		virtual BasePtr get_pointer() = 0;
	};

	template<class T>
	struct Storage : public Base
	{
		T value;//�洢��ֵ

		template<class U>
		Storage(U&& value_in) : value(forward<U>(value_in)){}
		
		BasePtr get_pointer() {
			return BasePtr(new Storage<T>(value));
		}

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
	
	any a1 = 25;
	any a2 = "ovo";
	any a3 = 3.1415;

	//ȡֵʱ���ͱ�����ԭ����ֵʱ��ͬ ���������쳣 ��Ϊ����ת��ʧ��
	cout << a1.cast<int>() << endl;
	cout << a2.cast<const char*>() << endl;
	cout << a3.cast<double>() << endl;
	
	a3 = "qwq";
	cout << a3.cast<const char*>() << endl;
	any a4(a1);
	cout << a4.cast<int>() << endl;

	cout << "=======================" << endl;

	any t[] = {a1, a2, a3, a4};
	cout << t[0].cast<int>() << endl;
	cout << t[1].cast<const char*>() << endl;
	cout << t[2].cast<const char*>() << endl;
	cout << t[3].cast<int>() << endl;

	cout << "=======================" << endl;

	any* k = new any[4];
	k[0] = a1;
	k[1] = a2;
	k[2] = a3;
	k[3] = a4;
	cout << k[0].cast<int>() << endl;
	cout << k[1].cast<const char*>() << endl;
	cout << k[2].cast<const char*>() << endl;
	cout << k[3].cast<int>() << endl;

	return 0; 
}