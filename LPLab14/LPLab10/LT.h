#pragma once
#define LEXEMA_FIXSIZE		1
#define LT_MAXSIZE			4096
#define LT_TI_NULLIDX		0xFFFFFFFF
#define LEX_INTEGER			't'
#define LEX_STRING			't'
#define LEX_ID				'i'
#define LEX_LITERAL			'l'
#define LEX_FUNCTION		'f'
#define LEX_DECLARE			'd'
#define LEX_RETURN			'r'
#define LEX_PRINT			'p'
#define LEX_MAIN			'm'
#define LEX_SEMICOLON		';'
#define LEX_COMMA			','
#define LEX_LEFTBRACE		'{'
#define LEX_RIGHTBRACE		'}'
#define LEX_LEFTBRACKET		'('
#define LEX_RIGHTBRACKET	')'
#define LEX_PLUS			'v'
#define LEX_MINUS			'v'
#define	LEX_STAR			'v'
#define LEX_SLASH			'v'

namespace LT
{
	struct Entry
	{
		char lexema[LEXEMA_FIXSIZE];
		int sn;
		int idxTI;
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry *table;
	};

	LexTable Create(int size);
	void Add(LexTable &lextable, Entry entry);
	Entry GetEntry(LexTable &lextable, int n);
	void Delete(LexTable &lextable);
}