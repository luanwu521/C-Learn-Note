#include <iostream>
#include <tuple>
using namespace std;

namespace tuple_helper {

	template<class T, class U>
	typename std::enable_if<std::is_convertible<T, U>::value || std::is_convertible<U, T>::value, bool>::type
	compare(T lhs, U rhs) {
		return lhs == rhs;
		//����enable_if��is_convertibleȷ���������͵Ķ�������໥ת�� �Ӷ����Խ��бȽ�
	}

	bool compare(...) {
		return false;//���κ��޷��Ƚϵ��������� ֱ�ӷ���false
	}

	//����ֵ�������� NΪtuple��Ԫ�صĸ��� TΪ������ֵ������ Args...Ϊtuple�Ĳ���
	template<int N, class T, class... Args>
	struct find_index
	{
		static int call(std::tuple<Args...>& tp, T&& value) {
			//�ݹ�+�ػ�����tuple��Ԫ��
			return(tuple_helper::compare(std::get<N - 1>(tp), value) ? N - 1 : find_index<N - 1, T, Args...>::call(tp, std::forward<T>(value)));
		}
	};

	template<class T, class... Args>
	struct find_index<1, T, Args...>
	{
		//�ݹ���ֹ �Ҳ���ָ��ֵ����-1
		static int call(std::tuple<Args...>& tp, T&& value) {
			return tuple_helper::compare(std::get<0>(tp), value) ? 0 : -1;
		}
		
	};
}

//ֵ��������������
template<class T, class... Args>
int find_index(std::tuple<Args...>& tp, T&& value) {
	//����sizeof...()��ȡtupleԪ�ظ���
	return tuple_helper::find_index<sizeof...(Args), T, Args...>::call(tp, std::forward<T>(value));
}


int main() {
	
	/*
		tuple_helper��һ��tuple��������
		��װ��һЩtuple�ĳ������� ��:���� ����ֵ��ȡ������
		��ʵ�ֻ��ڱ��ģ�� ģ���Ƶ��ڱ�����ִ�� ��������Ż�����ʱ��
	*/

	//��װ����ֻ��Ҫ����tuple����ʹ���ֵ����
	//�ŵ��������ǲ��س���˽�ĳ��tuple����ľ���ϸ�� ��:�������� �������͵�
	std::tuple<int, double, string> tp = std::make_tuple(1, 2.33, "ouo");
	cout << find_index(tp, 2.33) << endl;
	cout << find_index(tp, 666) << endl;//�Ҳ���

	return 0;
}