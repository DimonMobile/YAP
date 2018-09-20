#pragma once

#include "IT.h"
#include "LT.h"

#include <string>
#include <list>


class Parser
{
	enum class State
	{
		Token,
		StringLiteral
	} m_state;

	int m_line, m_position;
	LT::LexTable m_lexTable;
	IT::IdTable m_idTable;
	std::string m_token;
	void checkToken();
	void commitToken();
public:
	void putChar(const unsigned char ch);
	Parser();
	~Parser();
};

