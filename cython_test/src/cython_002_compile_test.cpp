#include <iostream>
#include "Python.h"
#include "marshal.h"
#include "cython_test.h"

int compile_test()
{
	if (python_init() < 0)
	{
		return -1;
	}

	int fileSize = 61;

	/// <summary>
	/// 源文件的路径
	/// </summary>
	/// <returns></returns>
	const char* fileName = R"(.\py\testm.py)";

	/// <summary>
	/// 生成文件的路径
	/// </summary>
	/// <returns></returns>
	const char* pycFileName = R"(.\py\testm273.pyc)";

	// 文本文件有可能没有结尾，多增加一个字节来做终止符号
	char* code = new char[fileSize+1];

	FILE* pyf;
	fopen_s(&pyf, fileName, "rb");
	if (!pyf)
	{
		printf_s("File Open fail %s \n",fileName);
		return -2;
	}

	fread_s(code, fileSize, 1, fileSize, pyf);
	fclose(pyf);

	// 修改结尾为终止符号
	code[fileSize] = 0;

	PyObject* p = Py_CompileString(code, "testm", Py_file_input);

	if (!p)
	{
		printf_s("Py_CompileString fail\n");
		return -3;
	}
	
	fopen_s(&pyf, pycFileName, "wb+");

	if (!pyf)
	{
		printf_s("File Open fail %s \n", pycFileName);
		return -4;
	}

	// 使用 marshal dump 导出 marshal 格式的内容
	// 经测试，有问题，问题未知，推测可能原因是其内部实现为memset，可能最开始的文件流长度不够
	//PyMarshal_WriteLongToFile(666, pyf2, 2);
	//PyMarshal_WriteObjectToFile(p, pyf2, Py_MARSHAL_VERSION);

	// 改用直接读写字节的形式
	char* cc = (char*)PyMarshal_WriteObjectToString(p, Py_MARSHAL_VERSION);

	/// <summary>
	/// 声明一个 PyMarshal_WriteObjectToString 的头结构
	/// </summary>
	/// <returns></returns>
	struct Py_String_ObjectHeader
	{
		INT32 Number;
		INT32 TypeCode;
		INT32 Size;
		INT32 Mask;
	};

	union UPy_String_ObjectHeader
	{
		Py_String_ObjectHeader* header;
		char* bytes;
	} UHeader;

	UHeader.bytes = cc;

	// 跳过 Py_String_ObjectHeader 12 字节 开始读取 MarshalString
	// 由于只有这里开头会保留 8 字节长度的 数据 和默认生成的 魔数 和 时间戳对齐，所以长度要 + 8
	fwrite(cc+12, 1, UHeader.header->Size+8, pyf);

	fflush(pyf);
	fclose(pyf);

	return 1;
}