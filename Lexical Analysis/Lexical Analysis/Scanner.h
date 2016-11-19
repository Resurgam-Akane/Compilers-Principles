#pragma once
/*
Author:xuzhu
Date:2016/10/4
Scanner
*/

#include <fstream>
#include <string>
#include "Token.h"
#include "Dictionary.h"

namespace LexicalAnalysis
{
	class Scanner
	{
	public:
		enum class State
		{
			NONE,
			END_OF_FILE,
			IDENTIFIER_OR_KEYWORD,
			NUM,
			STR_OR_CHAR,
			OPERATOR,
		};

		explicit Scanner(const std::string& filename);
		Token GetToken() const;
		Token GetNextToken();
		static bool GetErrorFlag();
		static void SetErrorFlag(bool flag);

	private:
		void _GetNextChar();
		char _PeekChar();
		void _AddToBuffer(char c);
		void _ReduceBuffer();

		//id or operation
		void _MakeToken(TokenType tt, TokenValue tv, const TokenLocation& loc, std::string name, int symbolPrecedence);
		
		//integer or char
		void _MakeToken(TokenType tt, TokenValue tv, const TokenLocation& loc, long intValue, std::string name);

		//real:float or double
		void _MakeToken(TokenType tt, TokenValue tv, const TokenLocation& loc, double realValue, std::string name);
		
		//string
		void _MakeToken(TokenType tt, TokenValue tv, const TokenLocation& loc, const std::string& strVale, std::string name);

		////char
		//void _MakeToken(TokenType tt, TokenValue tv, const TokenLocation& loc, const std::string& charVale, std::string name);

		void _HandleEOFState();
		void _HandleIdorKeyState();
		void _HandleNumberState();
		void _HandleStringState();
		void _HandleXInteger();
		void _HandleOctInteger();
		void _HandleDigit();
		void _HandleReal();
		void _HandleSci();
		void _HandleErrorID();
		void _HandleOperatorState();
		void _Preprocess();
		void _HandleLineComment();
		void _HandleBlockComment();
		TokenLocation   _GetTokenLocation() const;

		void _ErrorReport(const std::string& msg);

		std::string _filename;
		std::ifstream _input;
		unsigned int _line;
		unsigned int _column;
		TokenLocation _loc;
		char _currentchar;
		State _state;
		Token _token;
		Dictionary _dictionary;
		std::string _buffer;
		static bool _errorFlag;

	};

	inline Token Scanner::GetToken() const
	{
		return _token;
	}

	inline bool Scanner::GetErrorFlag()
	{
		return _errorFlag;
	}

	inline TokenLocation Scanner::_GetTokenLocation() const
	{
		return TokenLocation(_filename, _line, _column);
	}
}