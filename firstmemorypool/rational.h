#pragma once
/*
分数类型
该类型通过重载new和delete操作符实现自身内存的重复利用
*/
union NodeOfFreeList
{
public:
	NodeOfFreeList* m_next = nullptr;
	char m_address[1];
};
class Rational
{
public:
	Rational(int elem1, int elem2);

	void* operator new(size_t size);
	void operator delete(void* doomed, size_t size);
private:
	static void expandFreeList();
	static NodeOfFreeList* s_freeList;
	enum
	{
		EXPAND_SIZE = 32
	};
	int n = 0;//分子
	int d = 0;//分母
};
NodeOfFreeList* Rational::s_freeList = nullptr;
