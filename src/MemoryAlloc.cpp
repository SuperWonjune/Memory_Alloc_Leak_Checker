// MemoryAlloc.cpp

#include "MemoryAlloc.h"

// ���ø� ������� ������Ͽ��� ������ �Լ� ���

// pType * MemoryAlloc(AllocInfo * allocFile, int dataNum, char * fileName, int fileLine);
// void MemoryRelease(AllocInfo * allocFile, pType * ptr);


void PrintAlloc(AllocInfo * allocFile, size_t totalCount, size_t totalSize, size_t maxFileNum)
{

	std::cout << "Total Alloc Size : " << totalSize << std::endl;
	std::cout << "Total Alloc Count : " << totalCount << std::endl << std::endl;

	for (int i = 0; i < maxFileNum; i++) {
		// ���� �������� ���� �����Ͱ� ��� ����ü�� is_used bool ���� true
		if (allocFile[i].is_used == true) {

			std::cout << "Not Released Memory : [" << allocFile[i].ptr << "] " << allocFile[i].size << "Bytes" << std::endl;
			std::cout << "File : " << allocFile[i].fileName << " : " << allocFile[i].fileLine << std::endl << std::endl;

		}
	}
	
	
}