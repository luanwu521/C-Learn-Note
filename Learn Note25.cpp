#include <iostream>
#include <windows.h>
using namespace std;

bool Change_RegTable_DWORD(const char* Path, const char* KeyName, DWORD Data, HKEY Root = HKEY_CURRENT_USER) {
	bool retvalue = true;
	HKEY key;
	RegCreateKeyExA(Root, Path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	if (RegSetValueExA(key, KeyName, 0, REG_DWORD, (BYTE*)&Data, sizeof(Data)) != ERROR_SUCCESS) {
		retvalue = false;
	}
	RegCloseKey(key);
	return retvalue;
}

bool Change_RegTable_SZ(const char* Path, const char* KeyName, const char* Data, HKEY Root = HKEY_CURRENT_USER) {
	bool retvalue = true;
	HKEY key;
	RegCreateKeyExA(Root, Path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	if (RegSetValueExA(key, KeyName, 0, REG_SZ, (BYTE*)Data, strlen(Data)) != ERROR_SUCCESS) {
		retvalue = false;
	}
	RegCloseKey(key);
	return retvalue;
}

bool Change_RegTable_BINARY(const char* Path, const char* KeyName, BYTE* Data, unsigned Count, HKEY Root = HKEY_CURRENT_USER) {
	bool retvalue = true;
	HKEY key;
	RegCreateKeyExA(Root, Path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	if (RegSetValueExA(key, KeyName, 0, REG_BINARY, (BYTE*)Data, Count) != ERROR_SUCCESS) {
		retvalue = false;
	}
	RegCloseKey(key);
	return retvalue;
}

int main() {

	//设置此项(PaintDesktopVersion)为1将在桌面上显示windows版本信息
	cout << Change_RegTable_DWORD("Control Panel\\Desktop", "PaintDesktopVersion", 1) << endl;
	
	cout << Change_RegTable_SZ("SOFTWARE\\Microsoft\\Windows NT", "TEST", "Hello c++") << endl;
	
	const unsigned n = 4;
	BYTE add[n] = {0xff, 0x45, 0x89, 0x27};
	cout << Change_RegTable_BINARY("SOFTWARE\\Microsoft\\Windows NT", "TEST2", add, n) << endl;

	return 0;
}