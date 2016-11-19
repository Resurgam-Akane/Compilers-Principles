#pragma once
/*
	Author:xuzhu
	Date:2016/10/4
	Lexical unit
*/

#include <string>
#include <iostream>
#include <tuple>
#include <map>
#include <cassert>

namespace LexicalAnalysis
{
	enum class TokenType
	{
		IDENTIFIER,
		KEYWORDS,
		CONSTANT,
		OPERATORS,
		DELIMITER,
		END_OF_FILE,

		UNKNOWN,
	};

	enum  class TokenValue
	{
		// KeyWords
		VOID,
		CHAR,
		INT,
		FLOAT,
		DOUBLE,

		SHORT,
		LONG,
		SIGNED,
		UNSIGNED,

		STRUCT,
		UNION,
		ENUM,
		TYPEDEF,
		SIZEOF,
		
		AUTO,
		STATIC,
		REGISTER,
		EXTERN,
		CONST,
		VOLATILE,

		RETURN,
		CONTINUE,
		BREAK,
		GOTO,

		IF,
		ELSE,
		SWITCH,
		CASE,
		DEFAULT,

		FOR,
		DO,
		WHILE,

		// operators
		// --Arithmetic operators
		ADDITION,						//a+b
		SUBTRACTION,						//a-b
		BASIC_ASSIGNMENT,				//a=b
		UNARY_PLUS,						//+a
		UNARY_MINUS,					//-a
		MULTIPLICATION_OR_INDIRECTION,	//a*b, *a
		DIVISION,						//a/b
		MODULO,							//a%b
		INC,							//++a, a++
		DEC,							//--b, b--

		// --Comparison operators
		EQUAL,							//a==b
		NOTEQUAL,						//a!=b
		GREATER,						//a>b
		LESS,							//a<b
		GREATER_OR_EQUAL,				//a>=b
		LESS_OR_EQUAL,					//a<=b

		// --Logical operators
		NOT,							//!a
		AND,							//a&&b
		OR,								//a||b

		// --Bitwise operation			
		BIT_NOT,						//~a
		BIT_AND_OR_ADDRESSOF,			//a&b,&a
		BIT_OR,							//a|b
		BIT_XOR,						//a^b
		LEFTSHIFT,						//a<<b
		RIGHTSHIFT,						//a>>b

		// --Compound assignment operators
		ADD_ASSIGNMENT,					//a+=b
		SUB_ASSIGNMENT,					//a-=b
		MUL_ASSIGNMENT,					//a*=b
		DIV_ASSIGNMENT,					//a/=b
		MOD_ASSIGNMENT,					//a%=b
		BIT_AND_ASSIGNMENT,				//a&=b
		BIT_OR_ASSIGNMENT,				//a|=b
		BIT_XOR_ASSIGNMENT,				//a^=b
		LEFTSHIFT_ASSIGNMENT,			//a<<=b
		RIGHTSHIFT_ASSIGNMENT,			//a>>=b

		// --Member and pointer operators
		STRUCTURE_DEREFERENCE,			//a->b
		STRUCTURE_REFERENCE,			//a.b
		
		//other operator or symbol belong to DELIMITER
		LEFT_PAREN,						//(
		RIGHT_PAREN,					//)
		SEMICOLON,						//;
		LEFT_SUBSCRIPT,					//[
		RIGHT_SUBSCRIPT,				//]
		LEFT_BRACE,						//{
		RIGHT_BRACE,					//}
		QUES_MARK,						//?
		COLON,							//:
		COMMA,							//,

		UNRESERVED,
	};

	class TokenLocation
	{
	public:
		TokenLocation();
		TokenLocation(const std::string& fileName, unsigned int line, unsigned int column);
		std::string toString() const;
	private:
		std::string _filename;
		unsigned int _line;
		unsigned int _column;
	};

	class Token
	{
	public:
		Token();
		Token(TokenType type, TokenValue value, const TokenLocation& location,
			std::string name, int symbolPrecedence);
		Token(TokenType type, TokenValue value, const TokenLocation& location,
			const std::string& strValue, std::string name);
		Token(TokenType type, TokenValue value, const TokenLocation& location,
			long intValue, std::string name);
		Token(TokenType type, TokenValue value, const TokenLocation& location,
			double realValue, std::string name);

		TokenType GetTokenType() const;
		TokenValue GetTokenValue() const;
		const TokenLocation& GetTokenLocation() const;
		std::string GetTokenName() const;

		int GetSymbolPrecedence() const;

		long GetIntValue() const;
		double GetRealValue() const;
		std::string GetStringValue() const;

		void Show(std::ostream& out = std::cout) const;

		std::string GetIdentifierName() const;

		std::string TokenTypeDescription() const;
		std::string toString() const;
	private:
		TokenType _type;
		TokenValue _value;
		TokenLocation _location;
		std::string _name;
		int _symbolPrecedence;

		long _intValue;
		double _realValue;
		std::string _strValue;
	};

	inline TokenType Token::GetTokenType() const
	{
		return _type;
	}

	inline TokenValue Token::GetTokenValue() const
	{
		return _value;
	}

	inline std::string Token::GetTokenName() const
	{
		return _name;
	}

	inline const TokenLocation& Token::GetTokenLocation() const
	{
		return _location;
	}

	inline long Token::GetIntValue() const
	{
		return _intValue;
	}

	inline double Token::GetRealValue() const
	{
		return _realValue;
	}

	inline std::string Token::GetStringValue() const
	{
		return _strValue;
	}

	inline int Token::GetSymbolPrecedence() const
	{
		return _symbolPrecedence;
	}

	inline std::string Token::GetIdentifierName() const
	{
		assert(_type == TokenType::IDENTIFIER && "Token type should be identifier.");
		return _name;
	}
}