// newAlloc.h
#ifndef _NEW_ALLOC
#define _NEW_ALLOC

#define MAX_MEMORY_ARRAY 100
#define MAX_FILE_NAME 256
#define LINE_MAX_CHAR 1000
#define ERROR_BUFFER_MAX 50000

// 에러메시지 열거형
enum ERROR_MESSAGE { NOALLOC, ARRAY, LEAK};

#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>

// allocmemoryInfo를 넣을 자료구조로 STL 함수는 쓸수 없다.. new delete가 내부적으로 있어서 코드가 계속 돈다 ㅠㅠ 
// std::list 쓰려다가 3시간 날림..
// 답안의 자료구조는 어떤식일까?


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
	// 할당시킨 줄의 순번
	size_t lineNum;
	// [] 형식으로 선언했는지 여부
	bool isArr;
	// 할당한 시간
	time_t allocatedTime;

	// 배열 현재 index 쓰고있는지 확인
	bool isUsed = false;
private:
};


// 메모리 관리 클래스
class MemoryAllocManage
{
public:
	MemoryAllocManage();
	~MemoryAllocManage();

	// 에러의 타입에 맞춰서 errorBuffer에 에러 메시지 추가
	void addErrorLog(int errorType, void * memoryPtr, size_t fileSize = 0, char * fileName = NULL, size_t fileLine = 0);
	// Leak 메모리 검색
	void searchForLeakMemory();
	// 에러 버퍼 출력
	void printBuffer();
	// 에러 버퍼 파일로 출력
	void makeErrorFile();
	

	// 동적 할당된 메모리들의 정보가 담겨 있는 MemoryInfo 클래스의 배열
	AllocMemoryInfo memoryArray[MAX_MEMORY_ARRAY];
	size_t memoryAllocatedSize;
	

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
