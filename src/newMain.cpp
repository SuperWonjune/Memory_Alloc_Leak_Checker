// main.cpp




#include <iostream>
#include "newAlloc.h"

// main에 포함해야하는건가?
#define new new(__FILE__, __LINE__)



int main()
{

	int * hi = new int;
	int * bye = new int;
	int * aa = hi;
	int * bb = hi;
	int * cc = NULL;

	delete hi;
	delete aa;
	delete bb;
	delete cc;

	

	return 0;
}