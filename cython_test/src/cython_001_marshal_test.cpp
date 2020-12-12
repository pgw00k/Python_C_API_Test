
#include <iostream>
#include "Python.h"
#include "marshal.h"

int python_init()
{
	//***python调用***//
	//初始化python模块
	Py_Initialize();

	// 检查初始化是否成功  
	if (!Py_IsInitialized())
	{
		printf_s("Py_IsInitialized fail");
		Py_Finalize();
		return -1;
	}

	printf_s("Python Version:%s\n", Py_GetVersion());

	return 1;
}

int marshal_test()
{
	if (python_init() < 0)
	{
		return -1;
	}

#ifdef _WIN64
	int fileSize = 241;
	int skipCount = 16;
	const char* fileName = R"(D:\Sword\dump\testm.pyc)";
#else
	int fileSize = 228;
	int skipCount = 8;
	const char* fileName = R"(.\py\testm273.pyc)";
#endif

	char* code = new char[fileSize];

	FILE* pyf;
	fopen_s(&pyf, fileName, "rb");
	if (!pyf)
	{
		printf_s("File Open fail");
		return -2;
	}

	fread_s(code, fileSize, 1, fileSize, pyf);

	PyObject* p = PyMarshal_ReadObjectFromString(code + skipCount, fileSize - skipCount);
	if (!p)
	{
		printf_s("PyMarshal_ReadObjectFromString fail");
		return -3;
	}

#ifdef _WIN64
	p = PyImport_ExecCodeModule("tm", p);
#else
	p = PyImport_ExecCodeModule((char*)"tm", p);
#endif

	PyRun_SimpleString("import tm\ntm.print_func('CPP')");
	PyErr_Print();

	int* c;
	scanf_s("%d", &c);

	return 1;
}

