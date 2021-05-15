#include <iostream>
using namespace std;

class String {
public:

	String() : buffer(new char[1]()), len(0) { *buffer = '\0'; }
	String(size_t size_in) : buffer(new char[size_in + 1]()), len(size_in) {}
	String(const String& rhs) : buffer(new char[rhs.len + 1]()), len(rhs.len) {
		std::copy(rhs.buffer, rhs.buffer + len, buffer);
	}
	String(const char* rhs) : buffer(new char[strlen(rhs) + 1]()), len(strlen(rhs)) {
		const char* it = rhs;
		char* temp = buffer;
		while (it && *it != '\0') {*temp++ = *it++;}
		*temp = '\0';
	}
	String(String&& rhs) noexcept : len(std::move(rhs.len)) {std::swap(buffer, rhs.buffer);}
	String& operator=(const char* rhs) {
		if (buffer != nullptr) delete[] buffer;
		buffer = new char[strlen(rhs) + 1]();
		len = strlen(rhs);
		const char* it = rhs;
		char* temp = buffer;
		while (it && *it != '\0') {*temp++ = *it++;}
		*temp = '\0';
		return *this;
	}
	String& operator=(const String& rhs) {
		if (rhs != *this) {
			if (buffer != nullptr) delete[] buffer;
			buffer = new char[rhs.len + 1]();
			len = rhs.len;
			std::copy(rhs.buffer, rhs.buffer + len, buffer);
		}
		return *this;
	}
	String& operator=(String&& rhs) noexcept {
		if (rhs != *this) {
			if (buffer != nullptr) delete[] buffer;
			buffer = new char[rhs.len + 1]();
			len = std::move(rhs.len);
			std::swap(buffer, rhs.buffer);
		}
		return *this;
	}
	~String() { if(buffer != nullptr) delete[] buffer; }
	
	String operator +(const String& rhs) {
		if (rhs.empty()) return *this;
		if (this->empty()) return rhs;
		String tm(len + rhs.len);
		char* it = tm.buffer;
		char* ts = buffer;
		for (size_t i = 0; i < len; i++) { *it++ = *ts++; }
		char* it2 = rhs.buffer;
		for (size_t i = 0; i < rhs.len; i++) { *it++ = *it2++; }
		*it = '\0';

		return tm;
	}
	char& operator [](const size_t pos) {
		if (pos >= 0 && pos < len && len > 0) return *(buffer + pos);
		return *(buffer + len - 1);
	}
	void operator +=(const String& rhs) {
		String temp = *this + rhs;
		*this = temp;
	}
	bool operator == (const String& rhs) const {
		char* _x = buffer;
		char* _y = rhs.buffer;
		if (len != rhs.len) return false;
		for (size_t i = 0; i < len; i++) { if (*_x++ != *_y++) return false;  }
		return true;
	};
	bool operator < (const String& rhs) const {
		if (len < rhs.len) return true;
		if (len > rhs.len) return false;
		char* _x = buffer;
		char* _y = rhs.buffer;
		for (size_t i = 0; i < len; i++) { if (*_x++ < *_y++) return true; }
		return false;
	};
	bool operator !=(const String& rhs) const { return !(*this == rhs); }
	bool operator >(const String& rhs) const { 
		if (*this == rhs) return false;
		return !(*this < rhs); 
	}

	const size_t size() const { return len; }
	const char* c_str() const { return buffer; }
	void swap(String& rhs) noexcept {
		std::swap(buffer, rhs.buffer);
		std::swap(len, rhs.len);
	}
	void reverse() {
		char* _x = buffer;
		char* _y = buffer + len - 1;
		for (size_t i = 0 ; i < len / 2; i++) {std::swap(*_x++, *_y--);}
	}
	bool empty() const { if (*(buffer + len) == '\0') return true; return false; }
	String cut(size_t _x = 0, size_t _y = 0) {
		if (_x > _y) return *this;
		if (_y >= len) _y = len;
		String temp(_y - _x);
		char* _n = temp.buffer;
		char* _m = buffer + _x;
		for (size_t i = _x; i < _y; i++) {*_n++ = *_m++;}
		*_n = '\0';
		return temp;
	}

private:
	char* buffer = nullptr;
	size_t len = 0;
};

int main() {

	String str1("12345678");
	str1.reverse();
	cout << str1.c_str() << endl;

	String str2("87654321");
	cout << (str1 == str2) << endl;

	str1 = "88887";
	str2 = "88888";
	cout << (str1 < str2) << endl;

	str1 = "987654";
	cout << str1.cut(1, 6).c_str() << endl;

	String str3;
	cout << str3.empty() << endl;

	str2 = str1 + str3;
	cout << str2.c_str() << endl;

	return  0;
}