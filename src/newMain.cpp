// main.cpp




#include <iostream>
#include "newAlloc.h"

// main�� �����ؾ��ϴ°ǰ�?
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