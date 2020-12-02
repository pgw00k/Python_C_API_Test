#include <iostream>
#include "Python.h"
#include "cython_test.h"

int runfile_test()
{
	if (python_init() < 0)
	{
		return -1;
	}

	int fileSize = 236;

	/// <summary>
	/// 源文件的路径
	/// </summary>
	/// <returns></returns>
	const char* fileName = R"(./py/build_pyself.py)";

	Py_DontWriteBytecodeFlag = 1;
	Py_NoSiteFlag = 1;
	Py_IgnoreEnvironmentFlag = 1;

	PyEval_InitThreads();

	int len = strlen(fileName);
	
	char code[255];

	std::string str1 = "exec(open('";
	str1.append(fileName);
	str1.append("').read())");

	PyRun_SimpleString(str1.c_str());

	return 1;
}