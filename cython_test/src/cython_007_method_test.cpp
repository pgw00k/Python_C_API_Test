#include "D:\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h"
#include "Python.h"
#include "cython_test.h"
#include "object.h"

// 要使用 Py_InitModule4 需要先把 object.h 中的 #define Py_TRACE_REFS 取消
// 这里直接修改了 CPython 的 头文件
// 如果使用的是绿色版的CPython 还需要指定 dll 和其他环境路径，否则Py下导入模块会失败

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
	/// 一定要有结尾处的 {NULL, NULL, 0,NULL}
	/// 否则会提示 `module functions cannot set METH_CLASS or METH_STATIC`
	/// PyMethodDef 参数应该是一个数组
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