#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL '\n'
#define IN_AVAILABLE_CHARS "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ�����������������������������������Ũ������������������������(){}',+*=-/;. \n\r\t"

namespace In
{
	struct IN
	{
		enum {T = 1024, F = 2048, I = 4096};
		int size;
		int lines;
		int ignor;
		unsigned char* text;
		int code[256];
		IN();
	};
	IN getin(wchar_t infile[]);
}