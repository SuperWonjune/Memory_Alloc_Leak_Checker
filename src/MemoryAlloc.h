// MemoryAlloc.h

#ifndef _MEMORY_ALLOC
#define _MEMORY_ALLOC

#include <iostream>;


// 할당된 메모리들의 정보가 담긴 구조체
typedef struct _alloc_info
{
	// 현재 위치가 배열에서 쓰이고있는지 확인
	bool is_used = false;
	// 할당된 메모리의 주소값
	void *ptr;
	// 할당된 메모리의 크기
	size_t size;
	// 할당 명령을 내린 파일
	char * fileName;
	// 몇번째줄에서 할당 명령을 내렸는지 확인
	int fileLine;
} AllocInfo;



// 메모리 할당
template <typename pType>
pType * MemoryAlloc(AllocInfo * allocFile, size_t dataNum, char * fileName, int fileLine)
{
	bool empty_Space_Found = false;

	
	// 매크로로 받아온 type으로 포인터 자료형 결정
	// 동적 할당
	pType * ptr = new pType[dataNum];

	for (int i = 0; i < MAX_ALLOC_FILES; i++) {
		// 배열의 공간을 찾았을 경우
		if (allocFile[i].is_used == false) {
			
			// 구조체 구성 요소 값들을 각각 대입

			// 동적 할당 받은 포인터 주솟값 대입
			allocFile[i].ptr = ptr;
			// 할당된 메모리의 크기를 대입
			allocFile[i].size = dataNum * sizeof(pType);
			// 할당을 실행한 파일의 이름을 대입
			allocFile[i].fileName = fileName;
			// 할당이 시작된 줄이 몇번째줄인지 대입
			allocFile[i].fileLine = fileLine;
			// 해당 index는 사용하고 있는 것으로 설정
			allocFile[i].is_used = true;

			empty_Space_Found = true;

			// 전체 할당된 사이즈에 현 사이즈를 더함
			total_Alloc_Size += allocFile[i].size;

			break;
		}
	}

	// 배열이 꽉 찼을 경우
	if (empty_Space_Found == false) {
		puts("더 이상 할당할 수 없습니다");
		return NULL;
	}

	return ptr;
}



// 메모리 해제
template <typename pType>
void MemoryRelease(AllocInfo * allocFile, pType * ptr)
{

	for (int i = 0; i < MAX_ALLOC_FILES; i++) {
		// 배열을 돌면서 파라메터 주솟값을 찾았을 경우
		if (allocFile[i].ptr == ptr && allocFile[i].is_used == true) {

			// 구조체에 저장되어있던 포인터 주솟값을 참조해 동적 할당 해제
			delete[]allocFile[i].ptr;

			// 해당 index는 사용안하게 설정
			allocFile[i].is_used = false;
		}
	}
}


// 해제되지 않은 누수된 메모리를 찾아서 출력
void PrintAlloc(AllocInfo * allocFile, size_t totalCount, size_t totalSize, size_t maxFileNum);


#endif // !_MEMORY_ALLOC
