#include "LT.h"
#include "Error.h"

namespace LT
{
	LexTable Create(int size)
	{
		LexTable result{ size, 0, new Entry[size] };
		return result;
	}

	void Add(LexTable &lextable, Entry entry)
	{
		if (lextable.size + 1 > lextable.maxsize)
			throw ERROR_THROW(103);
		lextable.table[lextable.size++] = entry;
	}

	Entry GetEntry(LexTable &lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable &lextable)
	{
		delete[] lextable.table;
	}
};