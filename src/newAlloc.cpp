// newAlloc.cpp

#include "newAlloc.h"



// 관리자 전역 선언
MemoryAllocManage memoryAlloc;
// 이걸 헤더파일에 넣으니까 오류가 난다. 질문


//--------------------------------------------------------------------------------------------------------
// class AllocMemoryInfo
//--------------------------------------------------------------------------------------------------------

AllocMemoryInfo::AllocMemoryInfo() {

}


AllocMemoryInfo::~AllocMemoryInfo() {

}

//--------------------------------------------------------------------------------------------------------
// class MemoryAllocManage
//--------------------------------------------------------------------------------------------------------


MemoryAllocManage::MemoryAllocManage() {


}

MemoryAllocManage::~MemoryAllocManage() {


}



void MemoryAllocManage::addErrorLog(char * errorType, void * memoryPtr, size_t fileSize, char * fileName, size_t fileLine) {

}



//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------

void * operator new (size_t size, char *File, int Line) {

	AllocMemoryInfo allocated_Memory;

	// 동적 할당
	void * ptr = malloc(size);

	if (ptr == NULL) {
		puts("메모리 할당 실패!");
		return NULL;
	}

	// allocated_Memory 객체 내의 멤버 변수들 설정
	allocated_Memory.memoryPtr = ptr;
	sprintf_s(allocated_Memory.fileName, File);
	allocated_Memory.isArr = false;
	allocated_Memory.memorySize = size;
	time(&allocated_Memory.allocatedTime);

	// 메모리 할당 관리자 객체에 포함된 리스트에 allocated_memory 객체를 추가 
	memoryAlloc.memoryList.push_back(allocated_Memory);

	return ptr;
}

void * operator new[](size_t size, char *File, int Line) {
	return NULL;
}

void operator delete (void * p, char *File, int Line) {

}

void operator delete[](void * p, char *File, int Line) {


}

void operator delete (void * p) {
	// 확인해야 할 요소
	// 1. 할당되지 않은 포인터를 해제하려고 시도

	// 리스트에서 해당 포인터의 이름을 검색
	std::list<AllocMemoryInfo>::iterator iter = std::find_if(memoryAlloc.memoryList.begin(), memoryAlloc.memoryList.end(),
		[&](AllocMemoryInfo const& allocMemory) { return allocMemory.memoryPtr == p; });

	// 포인터 값 탐색 실패
	if (iter == memoryAlloc.memoryList.end()) {
		// 에러 로그 추가
		memoryAlloc.addErrorLog("NOALLOC", p);
		return;
	}

	// 탐색에 성공했을 시 리스트에서 해당 포인터를 가진 객체 삭제
	memoryAlloc.memoryList.erase(iter);

	// 동적 할당 해제
	free(p);

}


void operator delete[](void * p) {

}