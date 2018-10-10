#include "IT.h"
#include "Error.h"

#include <cstring>

namespace IT
{
	IdTable Create(int size)
	{
		IdTable result = {size, 0, new Entry[size]};
		return result;
	}

	void Add(IdTable &idtable, Entry entry)
	{
		if (idtable.size + 1 > TI_MAXSIZE)
			throw ERROR_THROW(102);
		idtable.table[idtable.size++] = entry;
	}

	Entry GetEntry(IdTable &idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable &idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; ++i)
		{
			if (!strcmp(id, idtable.table[i].id))
				return idtable.table[i].idxfirstLE;
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable &idtable)
	{
		delete[] idtable.table;
	}
};