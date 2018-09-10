#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include <fstream>
#include <string>

namespace In
{
	IN In::getin(wchar_t infile[])
	{
		std::ifstream in(infile);
		if (!in.is_open())
			throw ERROR_THROW(110);
		IN res;
		int currentLine(0);
		int currentCol(0);
		std::string fullText;
		while (in)
		{
			++res.lines;
			std::string strLine;
			std::getline(in, strLine);
			strLine.append("\n");
			fullText.append(strLine);
		}
		res.text = new unsigned char[fullText.size() + 1];
		unsigned char * resPtr = res.text;
		for (size_t i = 0; i < fullText.size(); ++i)
		{
			if (res.code[*((unsigned char*)&fullText[i])] == IN::F)
				throw ERROR_THROW_IN(111, currentLine, currentCol)
			else if (res.code[*((unsigned char*)&fullText[i])] == IN::I)
				++res.ignor;
			else if (res.code[*((unsigned char*)&fullText[i])] != IN::T)
			{
				*resPtr = res.code[*((unsigned char*)&fullText[i])];
				++resPtr;
			}
			else
			{
				*resPtr = fullText[i];
				++resPtr;
			}
			if (fullText[i] == '\n')
			{
				++currentLine;
				currentCol = 0;
			}
			else
				++currentCol;
		}
		*resPtr = '\0';
		res.size = strlen((char*)res.text);
		return res;
	}
	IN::IN() : size(0), lines(0), ignor(0), code IN_CODE_TABLE, text(nullptr) {}
}