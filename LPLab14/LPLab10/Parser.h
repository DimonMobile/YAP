#pragma once

#include "IT.h"
#include "LT.h"

#include <string>

class Parser
{
	enum class State
	{
		Undefined,
		Identifier,
		String,
		Number,
		Keyword
	} m_state;

	LT::LexTable m_table;
	std::string m_token;

	void processUndefined(const char ch);
	void processIdentifier(const char ch);
	void processString(const char ch);
	void processNumber(const char ch);
	void processKeyword(const char ch);
public:
	void putChar(const char ch);
	Parser();
	~Parser();
};

