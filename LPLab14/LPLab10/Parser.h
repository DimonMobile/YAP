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

	enum class ParseWait
	{
		Any,
		Function,
		Main,
		LiteralAfterFunction,
		LeftBracketAfterFunction,
		RightBracketAfterFunction,
		ParamTypeOrRightBracket,
		ParamType,
		ParamName,
		ParamCommaOrRightBracket,
		BlockBeginsOrSemicolon,
		InBlockAny,
		InBlockDeclare,
		InBlockType,
		InBlockIdentifierOrFunction,
		InBlockIdentifierOrLiteral,
		InBlockLiteral,
		InBlockSemicolon,
		InBlockAssignment,
		InBlockExpression,
		InBlockReturn,
		EndBlockSemicolon
	} m_parseWait;

	int m_line, m_position;
	LT::LexTable m_lexTable;
	IT::IdTable m_idTable;
	std::string m_token;
	void checkToken();
	void commitToken();
	bool isTokenType();
	bool isTokenPredefinedWord();
	bool isTokenStringLiteral();
	bool isTokenNumberLiteral();
	bool isTokenValidIdentifierName();
	bool isTokenFunctionToken();
	bool isTokenLeftBracketToken();
	bool isTokenRightBracketToken();
	bool isTokenLeftBraceToken();
	bool isTokenRightBraceToken();
	bool isTokenSemicolonToken();
	bool isTokenCommaToken();
	bool isTokenDeclareToken();
	bool isTokenAssignmentToken();
	bool isTokenOperator();
	bool isTokenReturnToken();
	bool isTokenMainToken();
public:
	void putChar(const unsigned char ch);
	Parser();
	~Parser();
};

