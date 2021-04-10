#include <iostream>
using namespace std;

template<class T>
void copy_s(const T* _begin, const T* _end, T* _target) {
	size_t _size = _end - _begin;
	T* _temp = new T[_size];
	T* _temp_begin = _temp;
	T* _temp_end = _temp + _size;
	while (_begin != _end) *_temp_begin++ = *_begin++;
	_temp_begin = _temp;
	while (_temp_begin != _temp_end) *_target++ = *_temp_begin++;
	delete[] _temp;
}

template<class T>
struct arrayList {
public:
	arrayList() = default;
	arrayList(unsigned len) : pack(new T[len]), packSize(len) {}
	~arrayList() { delete[] pack; }

	unsigned size() { return listSize; }
	
	T& operator[](unsigned pos) {
		return check_pos(pos) ? pack[pos] : *pack;
	}
	void insert(const T value, unsigned pos) {
		if (check_pos(pos)) {
			if (listSize == packSize) reallocate(packSize * 2);//扩充到原来的两倍容量
			if (pos == 0 && listSize == 0) {
				pack[0] = T(value);
			}
			else {
				copy(pack + pos, pack + listSize, pack + pos + 1);
				pack[pos] = T(value);
			}
			listSize++;
		}
	}

private:
	T* pack;//底层数据存储结构是数组
	unsigned packSize = 0;
	unsigned listSize = 0;

	bool check_pos(const unsigned& pos) const { 
		if (listSize == 0) return pos == 0 ? true : false;
		else return pos >= 0 && pos < listSize;
	}
	void reallocate(unsigned new_size) {
		T* temp = new T[new_size > 0 ? new_size : 1];
		copy_s(pack, pack + listSize, temp);
		delete[] pack;
		pack = temp;
		packSize = new_size;
	}
};

int main()
{
	arrayList<int> arr1(10);
	for (int i = 0; i < 100; i++) {
		arr1.insert(i, 0);
	}
	
	for (int i = 0; i < 100; i++) {
		cout << arr1[i] << endl;
	}

	return 0;
}