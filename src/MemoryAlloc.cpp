// MemoryAlloc.cpp

#include "MemoryAlloc.h"

// 템플릿 사용으로 헤더파일에서 구현된 함수 목록

// pType * MemoryAlloc(AllocInfo * allocFile, int dataNum, char * fileName, int fileLine);
// void MemoryRelease(AllocInfo * allocFile, pType * ptr);


void PrintAlloc(AllocInfo * allocFile, size_t totalCount, size_t totalSize, size_t maxFileNum)
{

	std::cout << "Total Alloc Size : " << totalSize << std::endl;
	std::cout << "Total Alloc Count : " << totalCount << std::endl << std::endl;

	for (int i = 0; i < maxFileNum; i++) {
		// 아직 해제되지 않은 포인터가 담긴 구조체의 is_used bool 값은 true
		if (allocFile[i].is_used == true) {

			std::cout << "Not Released Memory : [" << allocFile[i].ptr << "] " << allocFile[i].size << "Bytes" << std::endl;
			std::cout << "File : " << allocFile[i].fileName << " : " << allocFile[i].fileLine << std::endl << std::endl;

		}
	}
	
	
}