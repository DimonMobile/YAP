#include "stdafx.h"
#include "Parser.h"
#include "Error.h"
#include "LT.h"

#include <iostream>
#include <locale>

Parser::Parser() : m_line(1), m_position(1)
{
	m_table = LT::Create(LT_MAXSIZE);
}

void Parser::checkToken()
{
	if (m_token == Constants::integerToken)
		m_lexems.push_back(LEX_INTEGER);
	else if (m_token == Constants::commaToken)
		m_lexems.push_back(LEX_COMMA);
	else if (m_token == Constants::declareToken)
		m_lexems.push_back(LEX_DECLARE);
	else if (m_token == Constants::functionToken)
		m_lexems.push_back(LEX_FUNCTION);
	else if (m_token == Constants::leftBraceToken)
		m_lexems.push_back(LEX_LEFTBRACE);
	else if (m_token == Constants::leftBracketToken)
		m_lexems.push_back(LEX_LEFTBRACKET);
	else if (m_token == Constants::mainToken)
		m_lexems.push_back(LEX_MAIN);
	else if (m_token == Constants::minusToken)
		m_lexems.push_back(LEX_MINUS);
	else if (m_token == Constants::plusToken)
		m_lexems.push_back(LEX_PLUS);
	else if (m_token == Constants::printToken)
		m_lexems.push_back(LEX_PRINT);
	else if (m_token == Constants::returnToken)
		m_lexems.push_back(LEX_RETURN);
	else if (m_token == Constants::rightBraceToken)
		m_lexems.push_back(LEX_RIGHTBRACE);
	else if (m_token == Constants::rightBracketToken)
		m_lexems.push_back(LEX_RIGHTBRACKET);
	else if (m_token == Constants::semicolonToken)
		m_lexems.push_back(LEX_SEMICOLON);
	else if (m_token == Constants::slashToken)
		m_lexems.push_back(LEX_SLASH);
	else if (m_token == Constants::starToken)
		m_lexems.push_back(LEX_STAR);
	else if (m_token == Constants::stringToken)
		m_lexems.push_back(LEX_STRING);
	else if (m_token == Constants::assignmentToken)
		m_lexems.push_back(LEX_ASSIGNMENT);
	else if (m_state == State::StringLiteral)
			m_lexems.push_back(LEX_LITERAL);
	else
	{
		bool allDigits = true;
		for (const char chr : std::as_const(m_token))
		{
			if (!isdigit(chr))
			{
				allDigits = false;
				break;
			}
		}
		if (allDigits)
			m_lexems.push_back(LEX_LITERAL);
		else
			m_lexems.push_back(LEX_ID);
	}
}

inline void Parser::commitToken()
{
	checkToken();
	m_token.clear();
}

void Parser::putChar(const unsigned char ch)
{
	if (m_state == State::StringLiteral)
	{
		if (ch == '\'')
		{
			commitToken();
			m_state = State::Token;
		}
		return;
	}

	if (isspace(ch))
	{
		if (m_token.empty())
		{

		}
		else
		{
			commitToken();
		}
	}
	else 
	{
		if (m_token.empty())
		{
			if (ch == '\'')
			{
				m_state = State::StringLiteral;
			}
			else
			{
				m_token += ch;
			}
		}
		else
		{
			unsigned char lastTokenChar = static_cast<unsigned char>(m_token[m_token.size() - 1]);
			if (islower( lastTokenChar ))
			{
				if (islower(ch))
				{
					m_token += ch;
				}
				else if (!isdigit(ch))
				{
					commitToken();
					m_token += ch;
				}
				else
					throw ERROR_THROW_IN(2, m_line, m_position);
			}
			else if (isdigit(lastTokenChar))
			{
				if (isdigit(ch))
				{
					m_token += ch;
				}
				else if (!isalpha(ch))
				{
					commitToken();
					m_token += ch;
				}
				else
					throw ERROR_THROW_IN(2, m_line, m_position);
			}
			else
			{
				commitToken();
				m_token += ch;
			}
		}
	}
	++m_position;
	if (ch == '\n')
	{
		m_position = 1;
		++m_line;
	}
}

Parser::~Parser()
{
	for (const char &item : std::as_const(m_lexems))
	{
		std::cout << item;
		if (item == ')' || item == ';' || item == '{' || item == '}')
			std::cout << std::endl;
	}
	LT::Delete(m_table);
}