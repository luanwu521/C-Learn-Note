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
	arrayList() : pack(new T[0]) {};
	arrayList(unsigned len) : pack(new T[len]), packSize(len) {}
	arrayList(const arrayList<T>& rhs) {
		copy(rhs);
	}
	~arrayList() { delete[] pack; }
	bool operator!=(const arrayList<T>& rhs) {
		return rhs.pack != this->pack;
	}
	arrayList<T>& operator=(const arrayList<T>& rhs) {
		if (*this != rhs) {//防止自赋值
			this->~arrayList();
			copy(rhs);
		}
		return *this;
	}
	
	unsigned size() { return listSize; }
	bool check_pos(const unsigned& pos) const {
		if (listSize == 0) return pos == 0 ? true : false;
		else return pos >= 0 && pos < listSize;
	}

	//增删改查
	T& operator[](unsigned pos) {return check_pos(pos) ? pack[pos] : *pack;}
	void insert(const T value, unsigned pos) {
		if (check_pos(pos)) {
			if (listSize == packSize) reallocate(packSize * 2);//扩充到原来的两倍容量
			if (pos == 0 && listSize == 0) {
				pack[0] = T(value);
			}
			else {
				copy_s(pack + pos, pack + listSize, pack + pos + 1);
				pack[pos] = T(value);
			}
			listSize++;
		}
	}
	void remove(unsigned pos) {
		if (check_pos(pos)) {
			(pack + pos)->~T();
			copy_s(pack + pos + 1, pack + listSize, pack + pos);
			listSize--;
		}
	}
	int search(const T value) {
		for (unsigned j = 0; j < listSize; j++) {
			if (*(pack + j) == value) return j;
		}
	}

private:
	T* pack;//底层数据存储结构是数组
	unsigned packSize = 0;
	unsigned listSize = 0;

	void copy(const arrayList& rhs) {
		packSize = rhs.packSize;
		pack = new T[rhs.packSize];
		copy_s(rhs.pack, rhs.pack + rhs.listSize, pack);
		listSize = rhs.listSize;
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
	for (int i = 0; i < 20; i++) {
		arr1.insert(i, 0);
	}
	arrayList<int> arr2(arr1);
	arrayList<int> arr3;
	arr1.remove(5);
	for (unsigned i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << " ";
	}
	cout << endl;

	for (unsigned i = 0; i < arr2.size(); i++) {
		cout << arr2[i] << " ";
	}
	cout << endl;

	arr3 = arr2;
	for (unsigned i = 0; i < arr3.size(); i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;

	return 0;
}