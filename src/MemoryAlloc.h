// MemoryAlloc.h

#ifndef _MEMORY_ALLOC
#define _MEMORY_ALLOC

#include <iostream>;


// �Ҵ�� �޸𸮵��� ������ ��� ����ü
typedef struct _alloc_info
{
	// ���� ��ġ�� �迭���� ���̰��ִ��� Ȯ��
	bool is_used = false;
	// �Ҵ�� �޸��� �ּҰ�
	void *ptr;
	// �Ҵ�� �޸��� ũ��
	size_t size;
	// �Ҵ� ����� ���� ����
	char * fileName;
	// ���°�ٿ��� �Ҵ� ����� ���ȴ��� Ȯ��
	int fileLine;
} AllocInfo;



// �޸� �Ҵ�
template <typename pType>
pType * MemoryAlloc(AllocInfo * allocFile, size_t dataNum, char * fileName, int fileLine)
{
	bool empty_Space_Found = false;

	
	// ��ũ�η� �޾ƿ� type���� ������ �ڷ��� ����
	// ���� �Ҵ�
	pType * ptr = new pType[dataNum];

	for (int i = 0; i < MAX_ALLOC_FILES; i++) {
		// �迭�� ������ ã���� ���
		if (allocFile[i].is_used == false) {
			
			// ����ü ���� ��� ������ ���� ����

			// ���� �Ҵ� ���� ������ �ּڰ� ����
			allocFile[i].ptr = ptr;
			// �Ҵ�� �޸��� ũ�⸦ ����
			allocFile[i].size = dataNum * sizeof(pType);
			// �Ҵ��� ������ ������ �̸��� ����
			allocFile[i].fileName = fileName;
			// �Ҵ��� ���۵� ���� ���°������ ����
			allocFile[i].fileLine = fileLine;
			// �ش� index�� ����ϰ� �ִ� ������ ����
			allocFile[i].is_used = true;

			empty_Space_Found = true;

			// ��ü �Ҵ�� ����� �� ����� ����
			total_Alloc_Size += allocFile[i].size;

			break;
		}
	}

	// �迭�� �� á�� ���
	if (empty_Space_Found == false) {
		puts("�� �̻� �Ҵ��� �� �����ϴ�");
		return NULL;
	}

	return ptr;
}



// �޸� ����
template <typename pType>
void MemoryRelease(AllocInfo * allocFile, pType * ptr)
{

	for (int i = 0; i < MAX_ALLOC_FILES; i++) {
		// �迭�� ���鼭 �Ķ���� �ּڰ��� ã���� ���
		if (allocFile[i].ptr == ptr && allocFile[i].is_used == true) {

			// ����ü�� ����Ǿ��ִ� ������ �ּڰ��� ������ ���� �Ҵ� ����
			delete[]allocFile[i].ptr;

			// �ش� index�� �����ϰ� ����
			allocFile[i].is_used = false;
		}
	}
}


// �������� ���� ������ �޸𸮸� ã�Ƽ� ���
void PrintAlloc(AllocInfo * allocFile, size_t totalCount, size_t totalSize, size_t maxFileNum);


#endif // !_MEMORY_ALLOC
