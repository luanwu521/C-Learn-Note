#include <iostream>
#include <functional>
#include <type_traits>
#include <windows.h>
#include <map>

using namespace std;

class DllHelper {
public:
	DllHelper() = default;
	DllHelper(const string& path) : hMod(LoadLibraryA(path.data())) {}
	~DllHelper() {
		if (FreeLibrary(hMod)) {
			hMod = nullptr;
		}
	}
	
	//ÿ�ֺ������в�ͬ�Ĳ������� �������� ����ֵ���� 
	//����ñ��ģ�庯��+type_traits���췺��ͨ�õ��ú���
	template <typename T, typename... Args>
	typename result_of<function<T>(Args...)>::type//��ȡf�ķ���ֵ����
	RunFunction(const string& funcName, Args&&... args) {
		auto f = GetFunction<T>(funcName);
		return f(std::forward<Args>(args)...);//��ֵ����+����ת�����������忽�� ������Դ
	}

private:
	HMODULE hMod = nullptr;
	map<string, FARPROC> function_map = map<string, FARPROC>();

	template <typename T>
	function<T> GetFunction(const string& funcName) {
		map<string, FARPROC>::iterator it = function_map.find(funcName);
		//������ȡ���������Ѽ��غ����б� ����뵽�����б� 
		//�Ժ��ȡ����ֱ�Ӳ�� ���������¼���
		if (it == function_map.end()) {
			auto addr = GetProcAddress(hMod, funcName.data());
			if (addr) {
				function_map.insert(make_pair(funcName, addr));
				it = function_map.find(funcName);
			}
		}
		return std::function<T>((T*)(it->second));
		//�Ժ���ָ�빹��std::function
		//T��һ������ǩ��
	}
};


int main() {

	return 0;
}