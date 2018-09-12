#include "stdafx.h"
#include "Parser.h"


Parser::Parser() : m_state(State::Undefined)
{
	m_table = LT::Create(LT_MAXSIZE);
}

void Parser::processUndefined(const char ch)
{
}

void Parser::processIdentifier(const char ch)
{
}

void Parser::processString(const char ch)
{
}

void Parser::processNumber(const char ch)
{
}

void Parser::processKeyword(const char ch)
{
}

void Parser::putChar(const char ch)
{
	switch (m_state)
	{
		case State::Undefined:
			processUndefined(ch);
			break;
		case State::Identifier:
			processIdentifier(ch);
			break;
		case State::Keyword:
			processKeyword(ch);
			break;
		case State::Number:
			processNumber(ch);
			break;
		case State::String:
			processNumber(ch);
			break;
	}
}

Parser::~Parser()
{
	LT::Delete(m_table);
}