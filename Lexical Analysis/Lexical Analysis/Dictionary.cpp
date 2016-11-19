/*
Author:xuzhu
Date:2016/10/4
Dic
*/

#include "Dictionary.h"
namespace LexicalAnalysis
{
	Dictionary::Dictionary()
	{
		/*
			The preference of operators is according to the website: 
			https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B
			for some operator(++,--,*,&),their preference may be changed in different code.
			(for example, in ++a and a++, we should ser their preference at syntax analysis.
		*/
		_AddToken("(", std::make_tuple(TokenValue::LEFT_PAREN, TokenType::DELIMITER, 40));
		_AddToken(")", std::make_tuple(TokenValue::RIGHT_PAREN, TokenType::DELIMITER, 40));
		_AddToken("[", std::make_tuple(TokenValue::LEFT_SUBSCRIPT, TokenType::DELIMITER, -1));
		_AddToken("]", std::make_tuple(TokenValue::RIGHT_SUBSCRIPT, TokenType::DELIMITER, -1));
		_AddToken(".", std::make_tuple(TokenValue::STRUCTURE_REFERENCE, TokenType::OPERATORS, 40));
		_AddToken("->", std::make_tuple(TokenValue::STRUCTURE_DEREFERENCE, TokenType::OPERATORS, 40));
		_AddToken("++", std::make_tuple(TokenValue::INC, TokenType::OPERATORS, 39));
		_AddToken("--", std::make_tuple(TokenValue::DEC, TokenType::OPERATORS, 39));
		_AddToken("+", std::make_tuple(TokenValue::UNARY_PLUS, TokenType::OPERATORS, 39));
		_AddToken("-", std::make_tuple(TokenValue::UNARY_MINUS, TokenType::OPERATORS, 39));
		_AddToken("!", std::make_tuple(TokenValue::NOT, TokenType::OPERATORS, 39));
		_AddToken("~", std::make_tuple(TokenValue::BIT_NOT, TokenType::OPERATORS, 39));
		_AddToken("*", std::make_tuple(TokenValue::MULTIPLICATION_OR_INDIRECTION, TokenType::OPERATORS, 39));
		_AddToken("&", std::make_tuple(TokenValue::BIT_AND_OR_ADDRESSOF, TokenType::OPERATORS, 39));
		_AddToken("/", std::make_tuple(TokenValue::DIVISION, TokenType::OPERATORS, 38));
		_AddToken("%", std::make_tuple(TokenValue::MODULO, TokenType::OPERATORS, 38));
		_AddToken("+", std::make_tuple(TokenValue::ADDITION, TokenType::OPERATORS, 37));
		_AddToken("-", std::make_tuple(TokenValue::SUBTRACTION, TokenType::OPERATORS, 37));
		_AddToken("<<", std::make_tuple(TokenValue::LEFTSHIFT, TokenType::OPERATORS, 36));
		_AddToken(">>", std::make_tuple(TokenValue::RIGHTSHIFT, TokenType::OPERATORS, 36));
		_AddToken("<", std::make_tuple(TokenValue::LESS, TokenType::OPERATORS, 35));
		_AddToken("<=", std::make_tuple(TokenValue::LESS_OR_EQUAL, TokenType::OPERATORS, 35));
		_AddToken(">", std::make_tuple(TokenValue::GREATER, TokenType::OPERATORS, 35));
		_AddToken(">=", std::make_tuple(TokenValue::GREATER_OR_EQUAL, TokenType::OPERATORS, 35));
		_AddToken("==", std::make_tuple(TokenValue::EQUAL, TokenType::OPERATORS, 34));
		_AddToken("!=", std::make_tuple(TokenValue::NOTEQUAL, TokenType::OPERATORS, 34));
		_AddToken("^", std::make_tuple(TokenValue::BIT_XOR, TokenType::OPERATORS, 32));
		_AddToken("|", std::make_tuple(TokenValue::BIT_OR, TokenType::OPERATORS, 31));
		_AddToken("&&", std::make_tuple(TokenValue::AND, TokenType::OPERATORS, 30));
		_AddToken("||", std::make_tuple(TokenValue::OR, TokenType::OPERATORS, 29));
		_AddToken("=", std::make_tuple(TokenValue::BASIC_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("+=", std::make_tuple(TokenValue::ADD_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("-=", std::make_tuple(TokenValue::SUB_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("*=", std::make_tuple(TokenValue::MUL_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("/=", std::make_tuple(TokenValue::DIV_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("%=", std::make_tuple(TokenValue::MOD_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("<<=", std::make_tuple(TokenValue::LEFTSHIFT_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken(">>=", std::make_tuple(TokenValue::RIGHTSHIFT_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("&=", std::make_tuple(TokenValue::BIT_AND_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("^=", std::make_tuple(TokenValue::BIT_XOR_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken("|=", std::make_tuple(TokenValue::BIT_OR_ASSIGNMENT, TokenType::OPERATORS, 27));
		_AddToken(",", std::make_tuple(TokenValue::COMMA, TokenType::DELIMITER, -1));
		_AddToken("{", std::make_tuple(TokenValue::LEFT_BRACE, TokenType::DELIMITER, -1));
		_AddToken("}", std::make_tuple(TokenValue::RIGHT_BRACE, TokenType::DELIMITER, -1));
		_AddToken(";", std::make_tuple(TokenValue::SEMICOLON, TokenType::DELIMITER, -1));
		_AddToken("?", std::make_tuple(TokenValue::QUES_MARK, TokenType::DELIMITER, -1));
		_AddToken(":", std::make_tuple(TokenValue::COLON, TokenType::DELIMITER, -1));


		_AddToken("void", std::make_tuple(TokenValue::VOID, TokenType::KEYWORDS, -1));
		_AddToken("char", std::make_tuple(TokenValue::CHAR, TokenType::KEYWORDS, -1));
		_AddToken("int", std::make_tuple(TokenValue::INT, TokenType::KEYWORDS, -1));
		_AddToken("float", std::make_tuple(TokenValue::FLOAT, TokenType::KEYWORDS, -1));
		_AddToken("double", std::make_tuple(TokenValue::DOUBLE, TokenType::KEYWORDS, -1));
		_AddToken("short", std::make_tuple(TokenValue::SHORT, TokenType::KEYWORDS, -1));
		_AddToken("long", std::make_tuple(TokenValue::LONG, TokenType::KEYWORDS, -1));
		_AddToken("signed", std::make_tuple(TokenValue::SIGNED, TokenType::KEYWORDS, -1));
		_AddToken("unsigned", std::make_tuple(TokenValue::UNSIGNED, TokenType::KEYWORDS, -1));
		_AddToken("struct", std::make_tuple(TokenValue::STRUCT, TokenType::KEYWORDS, -1));
		_AddToken("union", std::make_tuple(TokenValue::UNION, TokenType::KEYWORDS, -1));
		_AddToken("enum", std::make_tuple(TokenValue::ENUM, TokenType::KEYWORDS, -1));
		_AddToken("typedef", std::make_tuple(TokenValue::TYPEDEF, TokenType::KEYWORDS, -1));
		_AddToken("sizeof", std::make_tuple(TokenValue::SIZEOF, TokenType::KEYWORDS, -1));
		_AddToken("auto", std::make_tuple(TokenValue::AUTO, TokenType::KEYWORDS, -1));
		_AddToken("static", std::make_tuple(TokenValue::STATIC, TokenType::KEYWORDS, -1));
		_AddToken("register", std::make_tuple(TokenValue::REGISTER, TokenType::KEYWORDS, -1));
		_AddToken("extern", std::make_tuple(TokenValue::EXTERN, TokenType::KEYWORDS, -1));
		_AddToken("const", std::make_tuple(TokenValue::CONST, TokenType::KEYWORDS, -1));
		_AddToken("volatile", std::make_tuple(TokenValue::VOLATILE, TokenType::KEYWORDS, -1));
		_AddToken("return", std::make_tuple(TokenValue::RETURN, TokenType::KEYWORDS, -1));
		_AddToken("continue", std::make_tuple(TokenValue::CONTINUE, TokenType::KEYWORDS, -1));
		_AddToken("break", std::make_tuple(TokenValue::BREAK, TokenType::KEYWORDS, -1));
		_AddToken("goto", std::make_tuple(TokenValue::GOTO, TokenType::KEYWORDS, -1));
		_AddToken("if", std::make_tuple(TokenValue::IF, TokenType::KEYWORDS, -1));
		_AddToken("else", std::make_tuple(TokenValue::ELSE, TokenType::KEYWORDS, -1));
		_AddToken("switch", std::make_tuple(TokenValue::SWITCH, TokenType::KEYWORDS, -1));
		_AddToken("case", std::make_tuple(TokenValue::CASE, TokenType::KEYWORDS, -1));
		_AddToken("default", std::make_tuple(TokenValue::DEFAULT, TokenType::KEYWORDS, -1));
		_AddToken("for", std::make_tuple(TokenValue::FOR, TokenType::KEYWORDS, -1));
		_AddToken("do", std::make_tuple(TokenValue::DO, TokenType::KEYWORDS, -1));
		_AddToken("while", std::make_tuple(TokenValue::WHILE, TokenType::KEYWORDS, -1));


	}

	void Dictionary::_AddToken(std::string name,
		std::tuple<TokenValue, TokenType, int> tokenMeta)
	{
		_dictionary.insert(std::pair<decltype(name), decltype(tokenMeta)>(name, tokenMeta));
	}

	std::tuple<TokenType, TokenValue, int> Dictionary::Lookup(const std::string& name) const
	{
		TokenValue tokenValue = TokenValue::UNRESERVED;
		TokenType  tokenType = TokenType::IDENTIFIER;
		int        precedence = -1;
		auto iter = _dictionary.find(name);

		if (iter != _dictionary.end())
		{
			tokenValue = std::get<0>(iter->second);
			tokenType = std::get<1>(iter->second);
			precedence = std::get<2>(iter->second);
		}

		return std::make_tuple(tokenType, tokenValue, precedence);
	}

	bool Dictionary::HaveToken(const std::string& name) const
	{
		auto iter = _dictionary.find(name);

		if (iter != _dictionary.end())
		{
			return true;
		}

		return false;
	}
}