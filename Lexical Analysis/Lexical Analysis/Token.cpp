/*
Author:xuzhu
Date:2016/10/4
Lexical unit
*/

#include "Token.h"

namespace LexicalAnalysis
{
	TokenLocation::TokenLocation(const std::string& FileName, unsigned int line, unsigned int column) : _filename(FileName), _line(line), _column(column) {  }

	TokenLocation::TokenLocation() : _filename(""), _line(1), _column(0) {  }

	std::string TokenLocation::toString() const
	{
		return _filename + ":" + std::to_string(_line) + ":" + std::to_string(_column) + ":";
	}



	Token::Token() : _type(TokenType::UNKNOWN), _value(TokenValue::UNRESERVED), _location(std::string(""), 0, 0), _name(""), _symbolPrecedence(-1) {  }

	//symbol or operator
	Token::Token(TokenType type, TokenValue value, const TokenLocation& location,
		std::string name, int symbolPrecedence)
		: _type(type), _value(value), _location(location), _name(name),
		_symbolPrecedence(symbolPrecedence)
	{ }

	//str constant
	Token::Token(TokenType type, TokenValue value, const TokenLocation& location,
		const std::string& strValue, std::string name)
		: _type(type), _value(value), _location(location),
		_name(name), _symbolPrecedence(-1), _strValue(strValue)
	{ }

	//int constant
	Token::Token(TokenType type, TokenValue value, const TokenLocation& location,
		long intValue, std::string name)
		: _type(type), _value(value), _location(location),
		_name(name), _symbolPrecedence(-1), _intValue(intValue)
	{ }

	//real constant
	Token::Token(TokenType type, TokenValue value, const TokenLocation& location,
		double realValue, std::string name)
		: _type(type), _value(value), _location(location),
		_name(name), _symbolPrecedence(-1), _realValue(realValue)
	{ }

	std::string Token::TokenTypeDescription() const
	{
		std::string buffer;

		switch (_type)
		{
		case LexicalAnalysis::TokenType::IDENTIFIER:
			buffer = "identifier";
			break;
		case LexicalAnalysis::TokenType::KEYWORDS:
			buffer = "keywords";
			break;
		case LexicalAnalysis::TokenType::CONSTANT:
			buffer = "constant";
			break;
		case LexicalAnalysis::TokenType::OPERATORS:
			buffer = "operator";
			break;
		case LexicalAnalysis::TokenType::DELIMITER:
			buffer = "delimiter";
			break;
		case LexicalAnalysis::TokenType::END_OF_FILE:
			buffer = "end of file";
			break;
		case LexicalAnalysis::TokenType::UNKNOWN:
			buffer = "unknown";
			break;
		default:
			break;
		}
		return buffer;
	}

	std::string Token::toString() const
	{
		return std::string("Token Type: " + TokenTypeDescription() + "Token name: " + _name);
	}

	void Token::Show(std::ostream &out) const
	{
		/*out << _location.toString() << "\t" << TokenTypeDescription() << "\t"
			<< _name << "\t\t" << GetSymbolPrecedence() << std::endl;*/

		out << _location.toString() << "\t" << "( " << TokenTypeDescription() << " , " << _name << " )" << std::endl;
	}
}