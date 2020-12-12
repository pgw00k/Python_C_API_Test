#include "D:\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h"
#include "Python.h"
#include "cython_test.h"

int module_test()
{
	if (python_init() < 0)
	{
		return -1;
	}

	PyObject* map = PyImport_GetModuleDict();

	int size = PyDict_Size(map);

	printf_s("module size is %d \n", size);

	PyObject* keys = PyDict_Values(map);
	for (int i = 0; i < size; i++)
	{
		printf_s("key %d is %s \n",i, PyModule_GetName(PyList_GetItem(keys,i)));
	}

	return 1;
}