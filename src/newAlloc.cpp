// newAlloc.cpp

#include "newAlloc.h"

// 관리자 전역 선언
MemoryAllocManage memoryAlloc;
// 이건 도대체 어디 놔둬야하는건가? 질문



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
	// 아직 할당되지 않은 메모리 검사
	// 콘솔로 에러버퍼 메시지 출력
	// 그 후 에러버퍼 내용을 담은 txt 파일 생성
	searchForLeakMemory();
	printBuffer();
	makeErrorFile();
}


void MemoryAllocManage::searchForLeakMemory() {
	for (int i = 0; i < MAX_MEMORY_ARRAY; i++) {
		// 아직 사용되고 있는 배열을 찾을 시
		if (memoryAlloc.memoryArray[i].isUsed == true) {
			AllocMemoryInfo current_arr = memoryAlloc.memoryArray[i];
			addErrorLog(ERROR_MESSAGE::LEAK, current_arr.memoryPtr, current_arr.memorySize, current_arr.fileName, current_arr.lineNum);
		}

	}
}

void MemoryAllocManage::addErrorLog(int errorType, void * memoryPtr, size_t memorySize, char * fileName, size_t lineNum) {

	char errorLine[LINE_MAX_CHAR];

	// 에러 상황에 따라서 처리
	switch (errorType)
	{
	
	// 할당되지 않은 메모리를 해제하려고 시도했을 경우
	case ERROR_MESSAGE::NOALLOC :
		sprintf(errorLine, "%-10s [0x%08x]\n", "NOALLOC", memoryPtr);
		strcat(errorBuffer,errorLine);

		break;

	case ERROR_MESSAGE::ARRAY :
		sprintf(errorLine, "%-10s [0x%08x] [%6d]Bytes %s : %d\n", "ARRAY", memoryPtr, memorySize, fileName, lineNum);
		strcat(errorBuffer, errorLine);

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

void MemoryAllocManage::makeErrorFile() {
	// 파일 이름 형식 Alloc_YYYYMMDD_HHMMSS.txt 
	char fileName[27];

	// localtime_s 사용을 위한 시간 변수들
	time_t timer;
	struct tm time_data;

	timer = time(NULL);
	localtime_s( &time_data, &timer);
	
	// fileName 버퍼에 파일이름 입력
	sprintf_s(fileName, "Alloc_%d%02d%02d_%02d%02d%02d.txt", time_data.tm_year+1900 ,time_data.tm_mon+1, time_data.tm_mday,
															time_data.tm_hour,time_data.tm_min,time_data.tm_sec);

	// 파일 생성
	std::ofstream errorFileOut(fileName);
	// errorBuffer 내용을 파일로 전달
	errorFileOut << errorBuffer;
	errorFileOut.close();

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
	allocated_Memory.lineNum = Line;
	allocated_Memory.isArr = false;
	allocated_Memory.memorySize = size;
	time(&allocated_Memory.allocatedTime);

	for (int i = 0; i < MAX_MEMORY_ARRAY; i++) {
		if (memoryAlloc.memoryArray[i].isUsed == false) {
			// 배열로 복사
			memoryAlloc.memoryArray[i] = allocated_Memory;
			memoryAlloc.memoryArray[i].isUsed = true;
			memoryAlloc.memoryAllocatedSize++;

			break;
		}

	}
	return ptr;
}

void * operator new[](size_t size, char *File, int Line) {

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
	allocated_Memory.lineNum = Line;
	allocated_Memory.isArr = true;
	allocated_Memory.memorySize = size;
	time(&allocated_Memory.allocatedTime);

	for (int i = 0; i < MAX_MEMORY_ARRAY; i++) {
		if (memoryAlloc.memoryArray[i].isUsed == false) {
			// 배열로 복사
			memoryAlloc.memoryArray[i] = allocated_Memory;
			memoryAlloc.memoryArray[i].isUsed = true;
			memoryAlloc.memoryAllocatedSize++;

			break;
		}

	}
	return ptr;
}


void operator delete (void * p, char *File, int Line) {

}

void operator delete[](void * p, char *File, int Line) {


}

void operator delete (void * p) {


	// 확인해야 할 요소
	// 1. new[] 배열로 할당한걸 해제하려고 시도할 시 
	// 2. 할당되지 않은 포인터를 해제하려고 시도

	// 배열에서 해당 포인터의 이름을 검색
	for (int i = 0; i < MAX_MEMORY_ARRAY; i++) {
		if (memoryAlloc.memoryArray[i].isUsed == true) {
			// 찾았을시
			if (memoryAlloc.memoryArray[i].memoryPtr == p) {

				// 하지만 배열로 선언했을 경우에는 오류
				if (memoryAlloc.memoryArray[i].isArr == true) {
					memoryAlloc.addErrorLog(ERROR_MESSAGE::ARRAY, p, memoryAlloc.memoryArray[i].memorySize, memoryAlloc.memoryArray[i].fileName, memoryAlloc.memoryArray[i].lineNum);
					return;
				}
				memoryAlloc.memoryArray[i].isUsed = false;
				free(p);
				memoryAlloc.memoryAllocatedSize--;
				return;
			}

		}
			
	}
	
	// 포인터 값 탐색 실패
	memoryAlloc.addErrorLog(ERROR_MESSAGE::NOALLOC, p);	

}


void operator delete[](void * p) {

	// 확인해야 할 요소
	// 1. new로 할당한걸 해제하려고 시도할 시 
	// 2. 할당되지 않은 포인터를 해제하려고 시도

	// 배열에서 해당 포인터의 이름을 검색
	for (int i = 0; i < MAX_MEMORY_ARRAY; i++) {
		if (memoryAlloc.memoryArray[i].isUsed == true) {
			// 찾았을시
			if (memoryAlloc.memoryArray[i].memoryPtr == p) {

				// 하지만 그냥 new로 선언했을 경우에는 오류
				if (memoryAlloc.memoryArray[i].isArr == false) {
					memoryAlloc.addErrorLog(ERROR_MESSAGE::ARRAY, p, memoryAlloc.memoryArray[i].memorySize, memoryAlloc.memoryArray[i].fileName, memoryAlloc.memoryArray[i].lineNum);
					return;
				}
				memoryAlloc.memoryArray[i].isUsed = false;
				free(p);
				memoryAlloc.memoryAllocatedSize--;
				return;
			}

		}

	}

	// 포인터 값 탐색 실패
	memoryAlloc.addErrorLog(ERROR_MESSAGE::NOALLOC, p);

}