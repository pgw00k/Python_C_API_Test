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
	/// Դ�ļ���·��
	/// </summary>
	/// <returns></returns>
	const char* fileName = R"(.\py\testm.py)";

	/// <summary>
	/// �����ļ���·��
	/// </summary>
	/// <returns></returns>
	const char* pycFileName = R"(.\py\testm273.pyc)";

	// �ı��ļ��п���û�н�β��������һ���ֽ�������ֹ����
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

	// �޸Ľ�βΪ��ֹ����
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

	// ʹ�� marshal dump ���� marshal ��ʽ������
	// �����ԣ������⣬����δ֪���Ʋ����ԭ�������ڲ�ʵ��Ϊmemset�������ʼ���ļ������Ȳ���
	//PyMarshal_WriteLongToFile(666, pyf2, 2);
	//PyMarshal_WriteObjectToFile(p, pyf2, Py_MARSHAL_VERSION);

	// ����ֱ�Ӷ�д�ֽڵ���ʽ
	char* cc = (char*)PyMarshal_WriteObjectToString(p, Py_MARSHAL_VERSION);

	/// <summary>
	/// ����һ�� PyMarshal_WriteObjectToString ��ͷ�ṹ
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

	// ���� Py_String_ObjectHeader 12 �ֽ� ��ʼ��ȡ MarshalString
	// ����ֻ�����￪ͷ�ᱣ�� 8 �ֽڳ��ȵ� ���� ��Ĭ�����ɵ� ħ�� �� ʱ������룬���Գ���Ҫ + 8
	fwrite(cc+12, 1, UHeader.header->Size+8, pyf);

	fflush(pyf);
	fclose(pyf);

	return 1;
}