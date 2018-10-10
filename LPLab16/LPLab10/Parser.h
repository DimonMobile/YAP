#pragma once

#include "IT.h"
#include "LT.h"
#include "Log.h"

#include <string>
#include <list>


class Parser
{
	enum class Type
	{
		String,
		Integer
	} m_type;

	bool m_isFunction;

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
		IdentifierAfterFunction,
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
		InBlockIdentifierOrFunctionOrExpression,
		InBlockIdentifierOrLiteral,
		InBlockLiteral,
		InBlockSemicolon,
		InBlockExpressionOrSemicolon,
		InBlockAssignment,
		InBlockExpression,
		InBlockReturn,
		InBlockPrint,
		EndBlockSemicolon,
	} m_parseWait;

	int m_line, m_position;
	Log::LOG m_log;
	LT::LexTable m_lexTable;
	IT::IdTable m_idTable;
	std::string m_token;
	void checkToken();
	void commitToken();
	void applyTokenType();
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
	bool isTokenPrintToken();
public:
	static std::string intToStr(int par, int precision = 3);
	void putChar(const unsigned char ch);
	void printLexems();
	void printIdentifiers();
	Parser(Log::LOG log);
	~Parser();
};

