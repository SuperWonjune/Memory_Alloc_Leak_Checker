// newAlloc.h
#ifndef _NEW_ALLOC
#define _NEW_ALLOC

#define MAX_MEMORY_ARRAY 100
#define MAX_FILE_NAME 256
#define LINE_MAX_CHAR 1000
#define ERROR_BUFFER_MAX 50000

// �����޽��� ������
enum ERROR_MESSAGE { NOALLOC, ARRAY, LEAK};

#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>

// allocmemoryInfo�� ���� �ڷᱸ���� STL �Լ��� ���� ����.. new delete�� ���������� �־ �ڵ尡 ��� ���� �Ф� 
// std::list �����ٰ� 3�ð� ����..
// ����� �ڷᱸ���� ����ϱ�?


// �Ҵ�� �޸��� ������ ����ִ� Ŭ����
class AllocMemoryInfo
{
public:
	AllocMemoryInfo();
	~AllocMemoryInfo();

	// �Ҵ�� �޸��� �ּ�
	void * memoryPtr;
	// �Ҵ� ����� �ִ� ������ �̸�
	char fileName[MAX_FILE_NAME];
	// �Ҵ��Ų �޸��� ũ��
	size_t memorySize;
	// �Ҵ��Ų ���� ����
	size_t lineNum;
	// [] �������� �����ߴ��� ����
	bool isArr;
	// �Ҵ��� �ð�
	time_t allocatedTime;

	// �迭 ���� index �����ִ��� Ȯ��
	bool isUsed = false;
private:
};


// �޸� ���� Ŭ����
class MemoryAllocManage
{
public:
	MemoryAllocManage();
	~MemoryAllocManage();

	// ������ Ÿ�Կ� ���缭 errorBuffer�� ���� �޽��� �߰�
	void addErrorLog(int errorType, void * memoryPtr, size_t fileSize = 0, char * fileName = NULL, size_t fileLine = 0);
	// Leak �޸� �˻�
	void searchForLeakMemory();
	// ���� ���� ���
	void printBuffer();
	// ���� ���� ���Ϸ� ���
	void makeErrorFile();
	

	// ���� �Ҵ�� �޸𸮵��� ������ ��� �ִ� MemoryInfo Ŭ������ �迭
	AllocMemoryInfo memoryArray[MAX_MEMORY_ARRAY];
	size_t memoryAllocatedSize;
	

private:
	// ���� �޽����� �����س��� ����
	char errorBuffer[ERROR_BUFFER_MAX];

};



// new, delete �����ε�

void * operator new (size_t size, char *File, int Line);
void * operator new[](size_t size, char *File, int Line);
void operator delete (void * p, char *File, int Line);
void operator delete[](void * p, char *File, int Line);
void operator delete (void * p);
void operator delete[](void * p);







#endif // ! _NEW_ALLOC
