#include<iostream>
using namespace std;
struct BlockBorder
{
	int BlockLength;
	bool Free() { return BlockLength > 0 ? true : false; }
	int MemorySize() { return BlockLength > 0 ? BlockLength : -BlockLength; }
	int BlockSize() { return MemorySize() + 2 * sizeof(int); }
};
struct FreeBlockHead :public BlockBorder
{
	FreeBlockHead* prior;
	FreeBlockHead* next;
};
class MemoryPool
{
public:
	MemoryPool(unsigned int size);
	~MemoryPool();
	void* Allocate(int size);
	void Free(void* p);
private:
	void InsertFreeBlock(void* p, int size);
	void SetUsedBorder(void* p, int size);
	void DeleteFreeBlock(FreeBlockHead* p);
	BlockBorder* GetPreBlock(void* p);
	BlockBorder* GetNextBlock(void* p);
	BlockBorder* GetCurrentBlock(void* p);
	char* m_Base;
	unsigned int m_PoolSize;
	FreeBlockHead* m_First;
};
MemoryPool::MemoryPool(unsigned int size)
{
	if (size <= 100)throw"size should be greater than 100.";
	m_Base = new char[size];
	if (!m_Base)throw"no enough memory";
	m_PoolSize = size;
	m_First = NULL;
	InsertFreeBlock(m_Base, size - 2 * sizeof(BlockBorder));
}
void MemoryPool::InsertFreeBlock(void* p, int size)
{
	FreeBlockHead * s = (FreeBlockHead *) p;
	s->BlockLength = size;
	p = (char*)p + size + sizeof(BlockBorder);
	((BlockBorder*)p)->BlockLength = size;
	if (m_First)m_First->prior = s;
	s->next = m_First;
	s->prior = NULL;
	m_First = s;
}
void MemoryPool::DeleteFreeBlock(FreeBlockHead* p)
{
	if (!p->next && !p->prior)
	{
		m_First = NULL;
	}
	else if (!p->next && p->prior)
	{
		p->prior->next = NULL;
	}
	else if (!p->prior)
	{
		p->next->prior = NULL;
		m_First = p->next;
	}
	else
	{
		p->next->prior = p->prior;
		p->prior->next = p->next;
	}
}
void MemoryPool::SetUsedBorder(void* p, int size)
{
	((BlockBorder*)p)->BlockLength = -size;
	p = (char*)p + sizeof(BlockBorder) + size;
	((BlockBorder*)p)->BlockLength = -size;
}
void* MemoryPool::Allocate(int size)
{
	if (m_First == NULL)return NULL;
	FreeBlockHead* p = m_First;
	while (p && p->MemorySize() < size)p = p->next;
	if (!p)return NULL;
	if (p->MemorySize() <= size + sizeof(FreeBlockHead) + sizeof(BlockBorder))
	{
		DeleteFreeBlock(p);
		SetUsedBorder(p, p->BlockLength);
		return (char*)p + sizeof(BlockBorder);
	}
	else
	{
		int newsize = p->MemorySize() - size - 2 * sizeof(BlockBorder);
		DeleteFreeBlock(p);
		InsertFreeBlock(p, newsize);
		SetUsedBorder((char*)p + p->BlockSize(), size);
		return (char*)p + p->BlockSize() + sizeof(BlockBorder);
	}
}
BlockBorder* MemoryPool::GetCurrentBlock(void* p)
{
	return(BlockBorder*)((char*)p - sizeof(BlockBorder));
}
BlockBorder* MemoryPool::GetPreBlock(void* p)
{
	char* cp = ((char*)p - sizeof(BlockBorder));
	if (cp == m_Base)return NULL;
	else
	{
		int len = *(int*)(cp - sizeof(BlockBorder));
		cp -= 2 * sizeof(BlockBorder) + (len < 0 ? -len : len);
		return (BlockBorder*)cp;
	}
}
BlockBorder* MemoryPool::GetNextBlock(void* p)
{
	BlockBorder* bp = GetCurrentBlock(p);
	char* cp = (char * )bp + bp->BlockSize();
	return(cp == m_Base + m_PoolSize) ? NULL : (BlockBorder*)cp;
}
void MemoryPool::Free(void* p)
{
	BlockBorder* currentBlock = GetCurrentBlock(p);
	BlockBorder* nextBlock = GetNextBlock(p);
	if (nextBlock && nextBlock->Free())
	{
		int size = nextBlock->BlockSize();
		DeleteFreeBlock((FreeBlockHead*)nextBlock);
		InsertFreeBlock(currentBlock, currentBlock->MemorySize() + size);
	}
	BlockBorder* preBlock = GetPreBlock(p);
	if (preBlock && preBlock->Free())
	{
		DeleteFreeBlock((FreeBlockHead*)preBlock);
		InsertFreeBlock(preBlock, preBlock->MemorySize() + currentBlock->BlockSize());
	}
	else
	{
		InsertFreeBlock(currentBlock, currentBlock->MemorySize());
	}
}
MemoryPool::~MemoryPool()
{
	cout << m_First << endl;
	cout << "size:" << m_First->MemorySize() << endl;
	if (m_Base)delete[]m_Base;
}
int main()
{
	MemoryPool a(256);
	try {
		char* p = (char*)a.Allocate(180);
		cout << (void*)p << endl;
		if (p)a.Free(p);
		p = (char*)a.Allocate(12);
		cout << (void*)p << endl;
		char* p1p = (char*)a.Allocate(92);
		cout << (void*)p1p << endl;
		char* p1 = (char*)a.Allocate(12);
		cout << (void*)p1 << endl;
		a.Free(p1);
		a.Free(p1p);
		a.Free(p);
	}
	catch (char* s) {
		cout << s << endl;
	}
}