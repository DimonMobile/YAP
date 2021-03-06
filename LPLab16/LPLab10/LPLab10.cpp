// LPLab10.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <locale>
#include <cwchar>

#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parser.h"
#include "MFST.h"

int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_ALL, "RUS");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Лексический анализ", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		//Logic here
		std::string fullSource(reinterpret_cast<char*>(in.text));
		std::string currentLine;
		size_t chainIdx{ 0 };
		size_t charIdx{ 0 };
		Parser parser(log);
		for (const char chr : fullSource)
			parser.putChar(chr);
		parser.printLexems();
		parser.printIdentifiers();
		MFST_TRACE_START;
		MFST::Mfst mfst(parser, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();
		mfst.printrules();
		//LP10 contineous here
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	return 0;
}

