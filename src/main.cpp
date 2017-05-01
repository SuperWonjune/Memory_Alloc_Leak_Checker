// main.cpp

#define MAX_ALLOC_FILES 1000

// MemoryAlloc 함수를 매크로로 래핑
#define _MemoryAlloc(type, size) \
	MemoryAlloc<type>(Allocated_Files, size, __FILE__, __LINE__); \
	total_Alloc_Count++

								
#include <iostream>

#include "MemoryAlloc.h"

// 메모리 할당이 호출된 총 횟수
size_t total_Alloc_Count = 0;
size_t total_Alloc_Size = 0;



int main()
{
	AllocInfo Allocated_Files[MAX_ALLOC_FILES];
	

	int *p4 = _MemoryAlloc(int, 1);
	int *p400 = _MemoryAlloc(int, 100);

	char *pZ1 = _MemoryAlloc(char, 50);
	char *pZ2 = _MemoryAlloc(char, 150);
	char *pZ3 = _MemoryAlloc(char, 60);
	char *pZ4 = _MemoryAlloc(char, 70);

	MemoryRelease(Allocated_Files, p4);
	//	MemoryRelease(p400);
	MemoryRelease(Allocated_Files, pZ1);
	//	MemoryRelease(pZ2);
	MemoryRelease(Allocated_Files, pZ3);
	MemoryRelease(Allocated_Files, pZ3);
	MemoryRelease(Allocated_Files, pZ4);

	PrintAlloc(Allocated_Files, total_Alloc_Count, total_Alloc_Size, MAX_ALLOC_FILES);


	return 0;
}