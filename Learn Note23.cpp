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
	
	//每种函数都有不同的参数类型 参数个数 返回值类型 
	//则采用变参模板函数+type_traits构造泛型通用调用函数
	template <typename T, typename... Args>
	typename result_of<function<T>(Args...)>::type//获取f的返回值类型
	RunFunction(const string& funcName, Args&&... args) {
		auto f = GetFunction<T>(funcName);
		return f(std::forward<Args>(args)...);//右值引用+完美转发避免无意义拷贝 消耗资源
	}

private:
	HMODULE hMod = nullptr;
	map<string, FARPROC> function_map = map<string, FARPROC>();

	template <typename T>
	function<T> GetFunction(const string& funcName) {
		map<string, FARPROC>::iterator it = function_map.find(funcName);
		//若待获取函数不在已加载函数列表 则加入到函数列表 
		//以后获取可以直接查表 不必再重新加载
		if (it == function_map.end()) {
			auto addr = GetProcAddress(hMod, funcName.data());
			if (addr) {
				function_map.insert(make_pair(funcName, addr));
				it = function_map.find(funcName);
			}
		}
		return std::function<T>((T*)(it->second));
		//以函数指针构造std::function
		//T是一个函数签名
	}
};


int main() {

	return 0;
}