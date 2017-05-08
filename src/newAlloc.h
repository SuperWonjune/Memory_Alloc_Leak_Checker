// newAlloc.h

#ifndef _NEW_ALLOC
#define _NEW_ALLOC

#define MAX_FILE_NAME 256
#define ERROR_BUFFER_MAX 2000

#include <algorithm>
#include <list>
#include <ctime>
#include <iostream>


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
	// [] �������� �����ߴ��� ����
	bool isArr;
	// �Ҵ��� �ð�
	time_t allocatedTime;
private:
};


// �޸� ���� Ŭ����
class MemoryAllocManage
{
public:
	MemoryAllocManage();
	~MemoryAllocManage();

	// ������ Ÿ�Կ� ���缭 errorBuffer�� ���� �޽��� �߰�
	void addErrorLog(char * errorType, void * memoryPtr, size_t fileSize = 0, char * fileName = NULL, size_t fileLine = 0);

	// ���� �Ҵ�� �޸𸮵��� ������ ��� �ִ� MemoryInfo Ŭ������ ����Ʈ
	std::list<AllocMemoryInfo> memoryList;

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
