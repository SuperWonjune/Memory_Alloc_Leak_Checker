// main.cpp

#include <iostream>
#include "newAlloc.h"

// main�� �����ؾ��ϴ°ǰ�?
#define new new(__FILE__, __LINE__)


int main()
{
	int * hi = new int;

	delete hi;

	return 0;
}