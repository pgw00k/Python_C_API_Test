// cython_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "cython_test.h"
#include<iostream>

int main()
{
	compile_test();
	marshal_test();

	int *c;
	scanf_s("%d",&c);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
