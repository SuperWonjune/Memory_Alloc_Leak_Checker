// main.cpp

#include <iostream>
#include "newAlloc.h"

// main에 포함해야하는건가?
#define new new(__FILE__, __LINE__)


int main()
{
	int * hi = new int;

	delete hi;

	return 0;
}