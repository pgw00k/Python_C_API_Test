// cython_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "cython_test.h"
#include<iostream>
#include <Windows.h>

inline HMODULE ModuleHandleByAddr(const void* ptrAddr)
{
	MEMORY_BASIC_INFORMATION info;
	VirtualQuery(ptrAddr, &info, sizeof(info));
	return (HMODULE)info.AllocationBase;
}
/*
 µ±Ç°Ä£¿é¾ä±ú
*/
inline HMODULE ThisModuleHandle()
{
	static HMODULE sInstance = ModuleHandleByAddr((void*)&ThisModuleHandle);
	return sInstance;
}

int main()
{

	int c = 0;
	scanf_s("%d", &c);

	switch (c)
	{
	case 1:
		compile_test();
		break;
	case 2:
		marshal_test();
		break;
	case 3:
		runfile_test();
		break;
	case 4:
		import_test();
		break;
	case 5:
		module_test();
		break;
	case 7:
		method_test();
		break;
	}

	scanf_s("%d", &c);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
