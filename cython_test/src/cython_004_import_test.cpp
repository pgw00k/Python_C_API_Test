#include <iostream>
#include "Python.h"
#include "cython_test.h"

int import_test()
{
	if (python_init() < 0)
	{
		return -1;
	}

	const char* mName = "testm";

	PyObject* module = PyString_InternFromString(mName);
	module = PyImport_Import(module);

	PyEval_CallMethod(module, "print_func", "s","Module");

	return 1;
}