#include "D:\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h"
#include "Python.h"
#include "cython_test.h"

int thread_test()
{
	if (python_init() < 0)
	{
		return -1;
	}


	return 1;
}