#include "D:\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h"
#include "Python.h"
#include "cython_test.h"
#include "object.h"

// Module method definitions
PyObject*  hello_world(PyObject* self, PyObject* args) {
	printf("Hello, method! \n");
	Py_RETURN_NONE;
}

int method_test()
{
	if (python_init() < 0)
	{
		return -1;
	}

	PyMethodDef ml = {
		"hello_world", hello_world, METH_NOARGS,
		"Print 'hello world' from a method defined in a C extension."
	};
	//ml.ml_name = "cHello";
	//ml.ml_meth = (PyCFunction)hello_world;
	//ml.ml_flags = METH_NOARGS;

	Py_InitModule4("c_ml", &ml, NULL, NULL, 1013);
	PyRun_SimpleString("import c_ml;c_ml.cHello()");

	return 1;
}