#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
using namespace std;

//����һ��ģ�庯�� �������������н�С���Ǹ�
//ģ�庯���Ĳ���������const����
template <typename T> T test1(const T& T1, const T& T2) {
	return (T1 < T2 ? T1 : T2);//T����֧�������<
}

//����һ��ģ����
template <typename T> class test2 {
public:
	typedef T value_type;
	typedef typename vector<T>::size_type size_type;
	//typename����������ŵĶ�����һ������ 
	//��Ϊ::���ܻᵼ�±�������Ϊ������ŵĶ�����һ����ĳ�Ա

	test2();
	test2(initializer_list<T> li);
	//����һ��initializer_list<T> ʵ����{}����ʼ����Ա

	void push_back(const T& t);
	T& operator[](size_type i);
	
	//��ģ������ʵ�ֳ�Ա����
	unsigned len() {
		return data->size();
	}

private:
	shared_ptr<vector<T>> data;//��������ָ�����vector
};

//��ģ������ʵ�ֳ�Ա�������� ��Ҫͨ��ģ��������ȷ����Ա����
template <typename T> test2<T>::test2(): data(make_shared<vector<T>>()){}
template <typename T> test2<T>::test2(initializer_list<T> li): data(make_shared<vector<T>>(li)){}
template <typename T> void test2<T>::push_back(const T& t){
	data->push_back(t);
}
template <typename T> T& test2<T>::operator[](size_type i) {
	return (i < data->size() ? (*data)[i] : (*data)[0]);
}

int main() {

	//ģ�庯�����Խ��ܲ�ͬ���͵�ʵ�� ʵ��ͬ���Ĺ���
	cout << test1(2, 3) << endl;//int
	cout << test1(3.14, 2.81) << endl;//double
	cout << test1('S', 'Q') << endl;//char
	
	//��Ϊ���캯������initializer_list<T> ���Կ�����{}����ʼ����Ա
	test2<int> A = { 1, 2, 3, 4, 5 };
	for (unsigned i = 0; i < A.len(); i++) {
		cout << A[i] << " " << ends;
	}
	cout << endl;

	test2<string> B = { "ovo", "qwq", "ouo" };
	B.push_back("qaq");
	for (unsigned i = 0; i < B.len(); i++) {
		cout << B[i] << " " << ends;
	}
	cout << endl;

	return 0;
}