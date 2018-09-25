#include "stdafx.h"
#include "Parser.h"
#include "Error.h"
#include "LT.h"

#include <iostream>
#include <locale>


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
} // namespace Constants

Parser::Parser() : m_line(1), m_position(1)
{
	m_lexTable = LT::Create(LT_MAXSIZE);
	m_idTable = IT::Create(TI_MAXSIZE);
	m_state = State::Token;
	m_parseWait = ParseWait::Any;
}

void Parser::checkToken()
{
	LT::Entry lexEntry;
	lexEntry.sn = m_line;
	lexEntry.idxTI = LT_TI_NULLIDX;
	if (m_token == Constants::integerToken)
		memcpy(lexEntry.lexema, LEX_INTEGER, LEXEMA_FIXSIZE);
	else if (m_token == Constants::commaToken)
		memcpy(lexEntry.lexema, LEX_COMMA, LEXEMA_FIXSIZE);
	else if (m_token == Constants::declareToken)
		memcpy(lexEntry.lexema, LEX_DECLARE, LEXEMA_FIXSIZE);
	else if (m_token == Constants::functionToken)
		memcpy(lexEntry.lexema, LEX_FUNCTION, LEXEMA_FIXSIZE);
	else if (m_token == Constants::leftBraceToken)
		memcpy(lexEntry.lexema, LEX_LEFTBRACE, LEXEMA_FIXSIZE);
	else if (m_token == Constants::leftBracketToken)
		memcpy(lexEntry.lexema, LEX_LEFTBRACKET, LEXEMA_FIXSIZE);
	else if (m_token == Constants::mainToken)
		memcpy(lexEntry.lexema, LEX_MAIN, LEXEMA_FIXSIZE);
	else if (m_token == Constants::minusToken)
		memcpy(lexEntry.lexema, LEX_MINUS, LEXEMA_FIXSIZE);
	else if (m_token == Constants::plusToken)
		memcpy(lexEntry.lexema, LEX_PLUS, LEXEMA_FIXSIZE);
	else if (m_token == Constants::printToken)
		memcpy(lexEntry.lexema, LEX_PRINT, LEXEMA_FIXSIZE);
	else if (m_token == Constants::returnToken)
		memcpy(lexEntry.lexema, LEX_RETURN, LEXEMA_FIXSIZE);
	else if (m_token == Constants::rightBraceToken)
		memcpy(lexEntry.lexema, LEX_RIGHTBRACE, LEXEMA_FIXSIZE);
	else if (m_token == Constants::rightBracketToken)
		memcpy(lexEntry.lexema, LEX_RIGHTBRACKET, LEXEMA_FIXSIZE);
	else if (m_token == Constants::semicolonToken)
		memcpy(lexEntry.lexema, LEX_SEMICOLON, LEXEMA_FIXSIZE);
	else if (m_token == Constants::slashToken)
		memcpy(lexEntry.lexema, LEX_SLASH, LEXEMA_FIXSIZE);
	else if (m_token == Constants::starToken)
		memcpy(lexEntry.lexema, LEX_STAR, LEXEMA_FIXSIZE);
	else if (m_token == Constants::stringToken)
		memcpy(lexEntry.lexema, LEX_STRING, LEXEMA_FIXSIZE);
	else if (m_token == Constants::assignmentToken)
		memcpy(lexEntry.lexema, LEX_ASSIGNMENT, LEXEMA_FIXSIZE);
	else if (m_state == State::StringLiteral)
	{
		memcpy(lexEntry.lexema, LEX_LITERAL, LEXEMA_FIXSIZE);

		IT::Entry tiEntry;
		tiEntry.iddatatype = IT::STR;
		tiEntry.idtype = IT::L;
	}
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
			memcpy(lexEntry.lexema, LEX_LITERAL, LEXEMA_FIXSIZE);
		else
			memcpy(lexEntry.lexema, LEX_ID, LEXEMA_FIXSIZE);
	}
	LT::Add(m_lexTable, lexEntry);
}

void Parser::commitToken()
{
	checkToken();

	if (m_parseWait == ParseWait::Any)
	{
		if (isTokenType())
			m_parseWait = ParseWait::Function;
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
	}
	else if (m_parseWait == ParseWait::Function)
	{
		if (isTokenFunctionToken())
			m_parseWait = ParseWait::LiteralAfterFunction;
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
	}
	else if (m_parseWait == ParseWait::LiteralAfterFunction)
	{
		if (isTokenValidIdentifierName())
		{
			// TODO: save to idientifier table
			m_parseWait = ParseWait::LeftBracketAfterFunction;
		}
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
	}
	else if (m_parseWait == ParseWait::LeftBracketAfterFunction)
	{
		if (isTokenLeftBracketToken())
			m_parseWait = ParseWait::ParamTypeOrRightBracket;
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
	}
	else if (m_parseWait == ParseWait::ParamTypeOrRightBracket)
	{
		if (isTokenRightBracketToken())
		{
			m_parseWait = ParseWait::BlockBeginsOrSemicolon;
		}
		else if (isTokenType())
		{
			m_parseWait = ParseWait::ParamName;
		}
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
	}
	else if (m_parseWait == ParseWait::ParamName)
	{
		if (isTokenValidIdentifierName())
		{
			m_parseWait = ParseWait::ParamCommaOrRightBracket;
		}
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
	}
	else if (m_parseWait == ParseWait::ParamCommaOrRightBracket)
	{
		if (isTokenComma())
			m_parseWait = ParseWait::ParamType;
		else if (isTokenRightBracketToken())
			m_parseWait = ParseWait::Any;
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
	}
	else if (m_parseWait == ParseWait::ParamType)
	{
		if (isTokenType())
			m_parseWait = ParseWait::ParamName;
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
	}
	else if (m_parseWait == ParseWait::BlockBeginsOrSemicolon)
	{
		if (isTokenSemicolonToken())
			m_parseWait = ParseWait::Any;
		else if (isTokenLeftBraceToken())
		{
			// TODO: block begins
		}
		else
			throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());
			
	}
	else
		throw ERROR_THROW_IN(3, m_line, m_position - m_token.size());

	m_token.clear();
}

bool Parser::isTokenType()
{
	if (   m_token == Constants::stringToken
		|| m_token == Constants::integerToken)
		return true;
	return false;
}

bool Parser::isTokenPredefinedWord()
{
	if (m_state == State::StringLiteral)
		return false;
	if (m_token == Constants::declareToken)
		return true;
	if (m_token == Constants::functionToken)
		return true;
	if (m_token == Constants::integerToken)
		return true;
	if (m_token == Constants::mainToken)
		return true;
	if (m_token == Constants::printToken)
		return true;
	if (m_token == Constants::returnToken)
		return true;
	if (m_token == Constants::stringToken)
		return true;
	return false;
}

bool Parser::isTokenStringLiteral()
{
	if (m_state == State::StringLiteral)
		return true;
	return false;
}

bool Parser::isTokenNumberLiteral()
{
	if (m_token.empty())
		return false;
	for (size_t i = 0; i < m_token.size(); ++i)
	{
		if (!isdigit(m_token[i]))
			return false;
	}
	return true;
}

bool Parser::isTokenValidIdentifierName()
{
	if (m_token.empty())
		return false;
	if (isTokenStringLiteral())
		return false;
	if (isTokenPredefinedWord())
		return false;
	for (size_t i = 0; i < m_token.size(); ++i)
	{
		if (!islower(m_token[i]))
			return false;
	}
	return true;
}

bool Parser::isTokenFunctionToken()
{
	if (m_state == State::StringLiteral)
		return false;
	if (m_token == Constants::functionToken)
		return true;
	return false;
}

bool Parser::isTokenLeftBracketToken()
{
	if (m_state == State::StringLiteral)
		return false;
	if (m_token == Constants::leftBracketToken)
		return true;
	return false;
}

bool Parser::isTokenRightBracketToken()
{
	if (m_state == State::StringLiteral)
		return false;
	if (m_token == Constants::rightBracketToken)
		return true;
	return false;
}

bool Parser::isTokenLeftBraceToken()
{
	if (m_state == State::StringLiteral)
		return false;
	if (m_token == Constants::rightBraceToken)
		return true;
	return false;
}

bool Parser::isTokenRightBraceToken()
{
	if (m_state == State::StringLiteral)
		return false;
	if (m_token == Constants::rightBraceToken)
		return true;
	return false;
}

bool Parser::isTokenSemicolonToken()
{
	if (m_state == State::StringLiteral)
		return false;
	if (m_token == Constants::semicolonToken)
		return true;
	return false;
}

bool Parser::isTokenComma()
{
	if (m_state == State::StringLiteral)
		return false;
	if (m_token == Constants::commaToken)
		return true;
	return false;
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
	for (int i = 0; i < m_lexTable.size; ++i)
	{
		std::cout << m_lexTable.table[i].lexema[0];
	}
	LT::Delete(m_lexTable);
	IT::Delete(m_idTable);
}