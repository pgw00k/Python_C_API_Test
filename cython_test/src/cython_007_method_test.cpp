#include "D:\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h"
#include "Python.h"
#include "cython_test.h"
#include "object.h"

// Ҫʹ�� Py_InitModule4 ��Ҫ�Ȱ� object.h �е� #define Py_TRACE_REFS ȡ��
// ����ֱ���޸��� CPython �� ͷ�ļ�
// ���ʹ�õ�����ɫ���CPython ����Ҫָ�� dll ����������·��������Py�µ���ģ���ʧ��

// Module method definitions
static PyObject*  hello_world(PyObject* self, PyObject* args) {
	printf("Hello, method! \n");
	Py_RETURN_NONE;
}

int method_test()
{
	if (python_init() < 0)
	{
		return -1;
	}

	/// <summary>
	/// һ��Ҫ�н�β���� {NULL, NULL, 0,NULL}
	/// �������ʾ `module functions cannot set METH_CLASS or METH_STATIC`
	/// PyMethodDef ����Ӧ����һ������
	/// https://stackoverflow.com/questions/11584765/integrating-c-and-python-valueerror-module-functions-cannot-set-meth-class-or
	/// </summary>
	/// <returns></returns>
	PyMethodDef mls[] = {
		{"cHello", hello_world, METH_NOARGS,NULL},
		{NULL, NULL, 0,NULL}
	};
	//ml.ml_name = "cHello";
	//ml.ml_meth = (PyCFunction)hello_world;
	//ml.ml_flags = METH_NOARGS;

	Py_InitModule4("c_ml", mls, NULL, NULL, 1013);
	//Py_InitModule("c_ml", mls);
	PyRun_SimpleString(R"(
print('Test cMethod!');
import c_ml;
print(dir(c_ml));
c_ml.cHello())");

	return 1;
}