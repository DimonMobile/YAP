#include "GRB.h"
#include <cstring>
#define GRB_ERROR_SERIES 600
namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)
	/*
		S -> m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S
		N -> dti; | rE; | i=E; | dtfi(F); | dti;N | re;N | i=E;N | dtfi(F);N
		E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
		M -> vE | vEM
		F -> ti | ti,F
		W -> i | l | i,W | l,W
	*/
	Greibach greibach(NS('S'), TS('$'), 6
			, Rule(NS('S'), GRB_ERROR_SERIES + 0, 3
				, Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'))
				, Rule::Chain(14, TS('t'), TS('f'), NS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S'))
				, Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')) )
			, Rule(NS('N'), GRB_ERROR_SERIES + 1, 8
				, Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';'))
				, Rule::Chain(3, TS('r'), NS('E'), TS(';'))
				, Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';'))
				, Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'))
				, Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N'))
				, Rule::Chain(4, TS('r'), TS('e'), TS(';'), NS('N'))
				, Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N'))
				, Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')) )
			, Rule(NS('E'), GRB_ERROR_SERIES + 2, 8
				, Rule::Chain(1, TS('i'))
				, Rule::Chain(1, TS('l'))
				, Rule::Chain(3, TS('('), NS('E'), TS(')'))
				, Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')'))
				, Rule::Chain(2, TS('i'), NS('M'))
				, Rule::Chain(2, TS('l'), NS('M'))
				, Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M'))
				, Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')) )
			, Rule(NS('M'), GRB_ERROR_SERIES + 3, 2
				, Rule::Chain(2, TS('v'), NS('E'))
				, Rule::Chain(3, TS('v'), NS('E'), NS('M')) )
			, Rule(NS('F'), GRB_ERROR_SERIES + 4, 2
				, Rule::Chain(2, TS('t'), TS('i'))
				, Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')) )
			, Rule(NS('W'), GRB_ERROR_SERIES + 5, 4
				, Rule::Chain(1, TS('i'))
				, Rule::Chain(1, TS('l'))
				, Rule::Chain(3, TS('i'), TS(','), NS('W'))
				, Rule::Chain(3, TS('l'), TS(','), NS('w')) )
		);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i];
	}

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; ++i)
			chains[i] = p[i];
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; ++i)
			rules[i] = p[i];
	}

	Greibach getGreibach()
	{
		return greibach;
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn)
			++k;
		if (k < size)
			prule = rules[rc = k];
		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size) 
			rc = rules[n];
		return rc;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; ++i)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
}