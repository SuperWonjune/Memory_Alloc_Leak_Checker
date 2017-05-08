// newAlloc.h

#ifndef _NEW_ALLOC
#define _NEW_ALLOC

#define MAX_FILE_NAME 256
#define ERROR_BUFFER_MAX 2000

#include <algorithm>
#include <list>
#include <ctime>
#include <iostream>


// 할당된 메모리의 정보가 담겨있는 클래스
class AllocMemoryInfo
{
public:
	AllocMemoryInfo();
	~AllocMemoryInfo();

	// 할당된 메모리의 주소
	void * memoryPtr;
	// 할당 명령이 있는 파일의 이름
	char fileName[MAX_FILE_NAME];
	// 할당시킨 메모리의 크기
	size_t memorySize;
	// [] 형식으로 선언했는지 여부
	bool isArr;
	// 할당한 시간
	time_t allocatedTime;
private:
};


// 메모리 관리 클래스
class MemoryAllocManage
{
public:
	MemoryAllocManage();
	~MemoryAllocManage();

	// 에러의 타입에 맞춰서 errorBuffer에 에러 메시지 추가
	void addErrorLog(char * errorType, void * memoryPtr, size_t fileSize = 0, char * fileName = NULL, size_t fileLine = 0);

	// 동적 할당된 메모리들의 정보가 담겨 있는 MemoryInfo 클래스의 리스트
	std::list<AllocMemoryInfo> memoryList;

private:
	// 에러 메시지를 저장해놓는 버퍼
	char errorBuffer[ERROR_BUFFER_MAX];

};


// new, delete 오버로딩

void * operator new (size_t size, char *File, int Line);
void * operator new[](size_t size, char *File, int Line);
void operator delete (void * p, char *File, int Line);
void operator delete[](void * p, char *File, int Line);
void operator delete (void * p);
void operator delete[](void * p);







#endif // ! _NEW_ALLOC
