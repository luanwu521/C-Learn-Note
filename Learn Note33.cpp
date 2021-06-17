#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

struct memory_manage {
	static inline void* allocate(size_t size) {
		return ::operator new(size);
	}
	static inline void* allocate(size_t n, size_t size) {
		return ::operator new(size * n);
	}
	static inline void deallocate(void* p) {
		delete static_cast<void*>(p);
	}
};

template<class T>
struct object_manage {
	static inline void construct(void* p) {
		new(static_cast<void*>(p)) remove_reference_t<T>;
	}
	static inline void construct(void* p, const T& x) {
		new(static_cast<void*>(p)) remove_reference_t<T>(x);
	}
	static inline void destory(void* p) {
		static_cast<T*>(p)->~T();
	}
};

template<class Iterator, class T>
Iterator fill_obj_n(Iterator p, size_t n, T&& x) {
	while (n--) 
		object_manage<remove_reference_t<T>>::construct(static_cast<void*>(&*p++), std::forward<T>(x));
	return static_cast<Iterator>(p);
}

template<class T, class U>
inline T my_static_cast(U& u) {
	return T(u);
}

class A {};
class B : A {};

int main() {
	
	string* p1 = static_cast<string*>(memory_manage::allocate(5, sizeof(string)));
	
	auto p2 = p1;
	fill_obj_n(p2, 5, string("hello"));
	int i = 5;
	while (i--)
		cout << *p2++ << endl;
	object_manage<string>::destory(--p2);
	object_manage<string>::construct(p2, "world");
	cout << *p2++ << endl;

	memory_manage::deallocate(p1);

	A* pa;
	B* pb;
	my_static_cast<B*>(pa);
	my_static_cast<A*>(pb);
	double k = 2.33;
	cout << my_static_cast<int>(k) << endl;

	return 0;
}