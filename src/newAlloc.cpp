// newAlloc.cpp

#include "newAlloc.h"

// ������ ���� ����
MemoryAllocManage memoryAlloc;
// �̰� ����ü ��� ���־��ϴ°ǰ�? ����



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
	memoryAllocatedSize = 0;
}

MemoryAllocManage::~MemoryAllocManage() {
	searchForLeakMemory();
	printBuffer();
}


void MemoryAllocManage::searchForLeakMemory() {
	for (int i = 0; i < MAX_MEMORY_ARRAY; i++) {
		// ���� ���ǰ� �ִ� �迭�� ã�� ��
		if (memoryAlloc.memoryArray[i].isUsed == true) {
			AllocMemoryInfo current_arr = memoryAlloc.memoryArray[i];
			addErrorLog(ERROR_MESSAGE::LEAK, current_arr.memoryPtr, current_arr.memorySize, current_arr.fileName, current_arr.lineNum);
		}

	}
}

void MemoryAllocManage::addErrorLog(int errorType, void * memoryPtr, size_t memorySize, char * fileName, size_t lineNum) {

	char errorLine[LINE_MAX_CHAR];

	// ���� ��Ȳ�� ���� ó��
	switch (errorType)
	{
	
	// �Ҵ���� ���� �޸𸮸� �����Ϸ��� �õ����� ���
	case ERROR_MESSAGE::NOALLOC :
		sprintf(errorLine, "%-10s [0x%08x]\n", "NOALLOC", memoryPtr);
		strcat(errorBuffer,errorLine);

		break;

	case ERROR_MESSAGE::ARRAY :
		

		break;

	case ERROR_MESSAGE::LEAK :
		sprintf(errorLine, "%-10s [0x%08x] [%6d]Bytes %s : %d\n", "LEAK", memoryPtr,memorySize,fileName,lineNum);
		strcat(errorBuffer, errorLine);

		break;
	default:
		break;
	}


}


void MemoryAllocManage::printBuffer() {
	puts(errorBuffer);
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
	allocated_Memory.lineNum = Line;
	allocated_Memory.isArr = false;
	allocated_Memory.memorySize = size;
	time(&allocated_Memory.allocatedTime);

	for (int i = 0; i < MAX_MEMORY_ARRAY; i++) {
		if (memoryAlloc.memoryArray[i].isUsed == false) {
			// �迭�� ����
			memoryAlloc.memoryArray[i] = allocated_Memory;
			memoryAlloc.memoryArray[i].isUsed = true;
			memoryAlloc.memoryAllocatedSize++;

			break;
		}

	}
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
	for (int i = 0; i < MAX_MEMORY_ARRAY; i++) {
		if (memoryAlloc.memoryArray[i].isUsed == true && memoryAlloc.memoryArray[i].memoryPtr == p) {
			// ã������
			memoryAlloc.memoryArray[i].isUsed = false;
			free(p);
			memoryAlloc.memoryAllocatedSize--;
			return;
		}

	}
	// ������ �� Ž�� ����
	memoryAlloc.addErrorLog(ERROR_MESSAGE::NOALLOC, p);	

}


void operator delete[](void * p) {

}