#pragma once

#include "IT.h"
#include "LT.h"

#include <string>

namespace Constants
{
	const std::string integerToken = "integer";
	const std::string stringToken = "string";
	const std::string functionToken = "function";
	const std::string declareToken = "declare";
	const std::string returnToken = "return";
	const std::string printToken = "print";
	const std::string mainToken = "main";
	const char semicolonToken = ';';
	const char commaToken = ',';
	const char leftBraceToken = '{';
	const char rightBraceToken = '}';
	const char leftBracketToken = '(';
	const char rightBracketToken = ')';
	const char plusToken = '+';
	const char minusToken = '-';
	const char starToken = '*';
	const char slashToken = '/';
};

class Parser
{
	enum class State
	{
		Undefined,
		String,
		Number,
		Token
	} m_state;

	int m_line, m_position;
	LT::LexTable m_table;
	std::string m_token;

	void processUndefined(const char ch);
	void processString(const char ch);
	void processNumber(const char ch);
	void processToken(const char ch);
public:
	void putChar(const char ch);
	Parser();
	~Parser();
};

