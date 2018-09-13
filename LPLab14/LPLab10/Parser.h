#pragma once

#include "IT.h"
#include "LT.h"

#include <string>
#include <list>

namespace Constants
{
	const std::string integerToken = "integer";
	const std::string stringToken = "string";
	const std::string functionToken = "function";
	const std::string declareToken = "declare";
	const std::string returnToken = "return";
	const std::string printToken = "print";
	const std::string mainToken = "main";
	const std::string semicolonToken = ";";
	const std::string commaToken = ",";
	const std::string leftBraceToken = "{";
	const std::string rightBraceToken = "}";
	const std::string leftBracketToken = "(";
	const std::string rightBracketToken = ")";
	const std::string plusToken = "+";
	const std::string minusToken = "-";
	const std::string starToken = "*";
	const std::string slashToken = "/";
	const std::string assignmentToken = "=";
};

class Parser
{
	enum class State
	{
		Token,
		StringLiteral
	} m_state;

	int m_line, m_position;
	LT::LexTable m_table;
	std::string m_token;
	std::list<char> m_lexems;
	void checkToken();
	void commitToken();
public:
	void putChar(const unsigned char ch);
	Parser();
	~Parser();
};

