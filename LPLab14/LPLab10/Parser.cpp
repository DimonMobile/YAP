#include "stdafx.h"
#include "Parser.h"

#include <cctype>

Parser::Parser() : m_state(State::Token) , m_line(1), m_position(1)
{
	m_table = LT::Create(LT_MAXSIZE);
}

void Parser::processUndefined(const char ch)
{

}

void Parser::processString(const char ch)
{
}

void Parser::processNumber(const char ch)
{
}

void Parser::processToken(const char ch)
{
	if (isspace(ch))
	{
		if (m_token.empty())
		{

		}
		else
		{

		}
	}
}

void Parser::putChar(const char ch)
{
	switch (m_state)
	{
		case State::Undefined:
			processUndefined(ch);
			break;
		case State::Token:
			processToken(ch);
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