// newAlloc.cpp

#include "newAlloc.h"



// ������ ���� ����
MemoryAllocManage memoryAlloc;
// �̰� ������Ͽ� �����ϱ� ������ ����. ����


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

	// ���� �Ҵ�
	void * ptr = malloc(size);

	if (ptr == NULL) {
		puts("�޸� �Ҵ� ����!");
		return NULL;
	}

	// allocated_Memory ��ü ���� ��� ������ ����
	allocated_Memory.memoryPtr = ptr;
	sprintf_s(allocated_Memory.fileName, File);
	allocated_Memory.isArr = false;
	allocated_Memory.memorySize = size;
	time(&allocated_Memory.allocatedTime);

	// �޸� �Ҵ� ������ ��ü�� ���Ե� ����Ʈ�� allocated_memory ��ü�� �߰� 
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
	// Ȯ���ؾ� �� ���
	// 1. �Ҵ���� ���� �����͸� �����Ϸ��� �õ�

	// ����Ʈ���� �ش� �������� �̸��� �˻�
	std::list<AllocMemoryInfo>::iterator iter = std::find_if(memoryAlloc.memoryList.begin(), memoryAlloc.memoryList.end(),
		[&](AllocMemoryInfo const& allocMemory) { return allocMemory.memoryPtr == p; });

	// ������ �� Ž�� ����
	if (iter == memoryAlloc.memoryList.end()) {
		// ���� �α� �߰�
		memoryAlloc.addErrorLog("NOALLOC", p);
		return;
	}

	// Ž���� �������� �� ����Ʈ���� �ش� �����͸� ���� ��ü ����
	memoryAlloc.memoryList.erase(iter);

	// ���� �Ҵ� ����
	free(p);

}


void operator delete[](void * p) {

}