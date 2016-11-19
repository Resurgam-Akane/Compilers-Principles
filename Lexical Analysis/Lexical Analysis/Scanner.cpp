/*
Author:xuzhu
Date:2016/10/4
Scanner
*/

#include <cctype>
#include "scanner.h"
#include "error.h"

namespace LexicalAnalysis
{
	bool Scanner::_errorFlag = false;

	Scanner::Scanner(const std::string& filename) : _filename(filename), _line(1), _column(0), _currentchar(0), _state(State::NONE)
	{
		_input.open(_filename);

		if (_input.fail()) {
			throw std::runtime_error("Fail to open the fail.");
		}
		else if (_filename.substr(_filename.size() - 2, 2) != ".c")
			throw std::runtime_error("it isn't a c source file.");
		else std::cout << "Open file successfully." << std::endl;
		//todo:write error report code.
	}

	void Scanner::_GetNextChar()
	{
		_currentchar = _input.get();

		if (_currentchar == '\n') {
			++_line;
			_column = 0;
		}
		else ++_column;
	}

	char Scanner::_PeekChar()
	{
		return _input.peek();
	}

	void Scanner::_AddToBuffer(char c)
	{
		_buffer.push_back(c);
	}

	void Scanner::_ReduceBuffer()
	{
		_buffer.pop_back();
	}

	//for operator
	void Scanner::_MakeToken(TokenType tt, TokenValue tv,
		const TokenLocation& loc, std::string name, int symbolPrecedence)
	{
		_token = Token(tt, tv, loc, name, symbolPrecedence);
		_buffer.clear();
		_state = State::NONE;
	}

	//for integer
	void Scanner::_MakeToken(TokenType tt, TokenValue tv,
		const TokenLocation& loc, long intValue, std::string name)
	{
		_token = Token(tt, tv, loc, intValue, name);
		_buffer.clear();
		_state = State::NONE;
	}

	//for real
	void Scanner::_MakeToken(TokenType tt, TokenValue tv,
		const TokenLocation& loc, double realValue, std::string name)
	{
		_token = Token(tt, tv, loc, realValue, name);
		_buffer.clear();
		_state = State::NONE;
	}

	//for char or string or Keyword
	void Scanner::_MakeToken(TokenType tt, TokenValue tv,
		const TokenLocation& loc, const std::string& strValue, std::string name)
	{
		_token = Token(tt, tv, loc, strValue, name);
		_buffer.clear();
		_state = State::NONE;
	}

	Token Scanner::GetNextToken()
	{
		bool matched = false;
		do
		{
			if (_state != State::NONE) matched = true;

			switch (_state)
			{
			case LexicalAnalysis::Scanner::State::NONE:
				_GetNextChar();
				break;
			case LexicalAnalysis::Scanner::State::END_OF_FILE:
				_HandleEOFState();
				break;
			case LexicalAnalysis::Scanner::State::IDENTIFIER_OR_KEYWORD:
				_HandleIdorKeyState();
				break;
			case LexicalAnalysis::Scanner::State::NUM:
				_HandleNumberState();
				break;
			case LexicalAnalysis::Scanner::State::STR_OR_CHAR:
				_HandleStringState();
				break;
			case LexicalAnalysis::Scanner::State::OPERATOR:
				_HandleOperatorState();
				break;
			default:
				_ErrorReport("Matched token state error.");
				break;
			}

			if (_state == State::NONE) {
				_Preprocess();

				if (_input.eof()) _state = State::END_OF_FILE;
				else {
					std::string s;
					s.push_back(_currentchar);
					if (std::isalpha(_currentchar) || _currentchar == '_') _state = State::IDENTIFIER_OR_KEYWORD;
					else if (std::isdigit(_currentchar) || _currentchar == '.') _state = State::NUM;
					else if (_currentchar == '\'' || _currentchar == '\"') _state = State::STR_OR_CHAR;
					else if (_dictionary.HaveToken(s))_state = State::OPERATOR;
					else _ErrorReport(_GetTokenLocation().toString() + " " + s + " is not in C character set.");
				}

			}
		} while (!matched);

		return _token;
	}

	void Scanner::_HandleEOFState()
	{
		_loc = _GetTokenLocation();
		_MakeToken(TokenType::END_OF_FILE, TokenValue::UNRESERVED, _loc, std::string("END_OF_FILE"), -1);
	}

	void Scanner::_HandleIdorKeyState()
	{
		_loc = _GetTokenLocation();
		_AddToBuffer(_currentchar);
		_GetNextChar();

		while (std::isalnum(_currentchar) || _currentchar == '_')
		{
			_AddToBuffer(_currentchar);
			_GetNextChar();
		}

		auto tokenMeta = _dictionary.Lookup(_buffer);
		_MakeToken(std::get<0>(tokenMeta), std::get<1>(tokenMeta), _loc, _buffer, std::get<2>(tokenMeta));
	}

	//todo: u
	void Scanner::_HandleNumberState()
	{
		_loc = _GetTokenLocation();
		int base = 10;
		bool isDouble = false, isSci = false, isError_ID = false;

		enum class NumState
		{
			INTERGER,
			REAL,
			SCI,
			ERROR_ID,
			DONE,
		};

		NumState state = NumState::INTERGER;

		if (_currentchar == '0' && (_PeekChar() == 'X' || _PeekChar() == 'x')) {
			base = 16;
			_AddToBuffer(_currentchar);
			_GetNextChar();
			_AddToBuffer(_currentchar);
		}
		else if (_currentchar == '0' && (_PeekChar() != '.')) {
			base = 8;
			//_AddToBuffer(_currentchar);
		}

		do
		{
			switch (state)
			{
			case NumState::INTERGER:
				if (base == 16) _HandleXInteger();
				else if (base == 8) _HandleOctInteger();
				else if (base == 10) _HandleDigit();
				break;
			case NumState::REAL:
				_HandleReal();
				isDouble = true;
				break;
			case NumState::SCI:
				_HandleSci();
				isSci = true;
				break;
			case NumState::ERROR_ID:
				_HandleErrorID();
				isError_ID = true;
				break;
			case NumState::DONE:
				break;
			default:
				_ErrorReport("Match number state error.");
				break;
			}

			if (_currentchar == '.') {
				if (isDouble) _ErrorReport("Fraction number can not have more than one dot.");
				else if (isSci) _ErrorReport("dot can not after e or E.");
				else if (base == 16) _ErrorReport("Hexadecimal number in C can only be integer.");
				else if (base == 8) _ErrorReport("Oct number in C can only be integer.");
				state = NumState::REAL;
			}
			else if (_currentchar == 'e' || _currentchar == 'E') {
				if (isDouble) state = NumState::SCI;
				else if (isSci) _ErrorReport("only one e or E is allowed.");
				else if (base == 16) _ErrorReport("Hexadecimal number in C can not have e or E.");
				else if (base == 8) _ErrorReport("Oct number in C can not have e or E.");
				state = NumState::SCI;
			}
			else if (isalpha(_currentchar)) {
				_ErrorReport("Id can not start with number.");
				state = NumState::ERROR_ID;
			}
			else state = NumState::DONE;
		} while (state != NumState::DONE);

		if (!GetErrorFlag()) {
			if (isDouble || isSci) _MakeToken(TokenType::CONSTANT, TokenValue::UNRESERVED, _loc, std::stod(_buffer), _buffer);
			else _MakeToken(TokenType::CONSTANT, TokenValue::UNRESERVED, _loc, std::stol(_buffer, 0, base), _buffer);
		}
		else {
			_buffer.clear();
			_state = State::NONE;
		}
	}

	void Scanner::_HandleStringState()
	{
		_loc = _GetTokenLocation();
		char firstmark = _currentchar, lastmark;
		
		enum class StringState
		{
			STRING_OR_CHAR,
			STRING_OR_CHAR_END,
			END_OF_FILE,
		};

		StringState state = StringState::STRING_OR_CHAR;

		_GetNextChar();
		do
		{
			switch (_currentchar)
			{
			case '\'': case '\"':
				if (isalnum(_PeekChar())) state = StringState::STRING_OR_CHAR;
				else {
					lastmark = _currentchar;
					state = StringState::STRING_OR_CHAR_END;
				}
				break;
			case EOF:
				state = StringState::END_OF_FILE;
				break;
			default:
				state = StringState::STRING_OR_CHAR;
				break;
			}

			if (state != StringState::STRING_OR_CHAR_END && state != StringState::END_OF_FILE) {
				_AddToBuffer(_currentchar);
				_GetNextChar();
			}

		} while (state != StringState::STRING_OR_CHAR_END && state != StringState::END_OF_FILE);

		if (state == StringState::STRING_OR_CHAR_END) {
			if (lastmark == firstmark && firstmark == '\'' && _buffer.length() == 1)
				_MakeToken(TokenType::CONSTANT, TokenValue::UNRESERVED, _loc, static_cast<long>(_buffer.at(0)), _buffer);
			else if (lastmark == firstmark && firstmark == '\"' && _buffer.length() != 1)
				_MakeToken(TokenType::CONSTANT, TokenValue::UNRESERVED, _loc, _buffer, _buffer);
			else _ErrorReport(std::string("char use \', string use \""));
			
			_GetNextChar();
		}
		else throw std::runtime_error(_loc.toString() + " Before EOF, a \" or \' is expected.");
	}

	//void Scanner::_HandleStringState()
	//{
	//	_loc = _GetTokenLocation();
	//	char firstmark = _currentchar, lastmark;
	//	bool match = false;

	//	enum class StringState
	//	{
	//		STRING_OR_CHAR,
	//		STRING_OR_CHAR_END,
	//		BLACKSLASH,
	//		END_OF_FILE,
	//	};

	//	StringState state = StringState::STRING_OR_CHAR;

	//	_GetNextChar();
	//	do
	//	{
	//		switch (_currentchar)
	//		{
	//		case EOF:
	//			state = StringState::END_OF_FILE;
	//			break;
	//		case '\'': case '\"':
	//			if (state == StringState::STRING_OR_CHAR) {
	//				state = StringState::STRING_OR_CHAR_END;
	//				lastmark = _currentchar;
	//			}
	//			else if (state == StringState::BLACKSLASH) state = StringState::STRING_OR_CHAR;
	//			break;
	//		case '\\':
	//			if (state == StringState::STRING_OR_CHAR) state = StringState::BLACKSLASH;
	//			else if (state == StringState::BLACKSLASH) state = StringState::STRING_OR_CHAR;
	//			break;
	//		case '0' : case 'a': case 'b': case 'f': case 'n': case 'r': case 't': case 'v': //todo:solve the ? bug.
	//			if (state == StringState::BLACKSLASH) state = StringState::STRING_OR_CHAR;
	//			break;
	//		default:
	//			if (state == StringState::STRING_OR_CHAR) state = StringState::STRING_OR_CHAR;
	//			break;
	//		}

	//		if (state != StringState::STRING_OR_CHAR_END && state != StringState::END_OF_FILE) {
	//			_AddToBuffer(_currentchar);
	//			/*if (_PeekChar() == EOF) break;
	//			else _GetNextChar();*/
	//			_GetNextChar();
	//		}
	//	} while (state != StringState::STRING_OR_CHAR_END && state != StringState::END_OF_FILE);

	//	if (state == StringState::STRING_OR_CHAR_END) {
	//		if (lastmark == firstmark && firstmark == '\'' && _buffer.length() == 1)
	//			_MakeToken(TokenType::CONSTANT, TokenValue::UNRESERVED, _loc, static_cast<long>(_buffer.at(0)), _buffer);
	//		else if (lastmark == firstmark && firstmark == '\"' && _buffer.length() != 1)
	//			_MakeToken(TokenType::CONSTANT, TokenValue::UNRESERVED, _loc, _buffer, _buffer);
	//		else _ErrorReport(std::string("char use \', string use \""));

	//		_GetNextChar();
	//	}
	//	else throw std::runtime_error(_loc.toString() + " miss \" to end the string.");
	//}

	void Scanner::_HandleOperatorState()
	{
		_loc = _GetTokenLocation();

		_AddToBuffer(_currentchar);

		if (_PeekChar() != EOF) _AddToBuffer(_PeekChar());

		if (_dictionary.HaveToken(_buffer) && _PeekChar() != EOF) _GetNextChar();
		else if (_PeekChar() != EOF) _ReduceBuffer();

		if ((_PeekChar() == '=') && ((_buffer == "<<") || (_buffer == ">>"))) {
			_GetNextChar();
			_AddToBuffer(_currentchar);
		}

		auto tokenmeta = _dictionary.Lookup(_buffer);
		_MakeToken(std::get<0>(tokenmeta), std::get<1>(tokenmeta), _loc, _buffer, std::get<2>(tokenmeta));

		_GetNextChar();
	}

	void Scanner::_HandleReal()
	{
		if (!std::isdigit(_PeekChar())) _ErrorReport("Fraction part must be number.");

		//eat .
		_AddToBuffer(_currentchar);
		_GetNextChar();

		while (std::isdigit(_currentchar)) {
			_AddToBuffer(_currentchar);
			_GetNextChar();
		}
	}

	void Scanner::_HandleXInteger()
	{
		bool readFlag = false;
		_GetNextChar();

		while (std::isxdigit(_currentchar)) {
			readFlag = true;
			_AddToBuffer(_currentchar);
			_GetNextChar();
		}

		if (!readFlag) _ErrorReport("Hexadecimal number format error.");
	}

	void Scanner::_HandleOctInteger()
	{
		bool readFlag = false;

		while (std::isdigit(_currentchar) && _currentchar < '8') {
			readFlag = true;
			_AddToBuffer(_currentchar);
			_GetNextChar();
		}

		if (!readFlag) _ErrorReport("Oct number format error.");
	}

	void Scanner::_HandleDigit()
	{
		_AddToBuffer(_currentchar);
		_GetNextChar();

		while (std::isdigit(_currentchar))
		{
			_AddToBuffer(_currentchar);
			_GetNextChar();
		}
	}

	void Scanner::_HandleSci()
	{
		_AddToBuffer(_currentchar);
		_GetNextChar();

		if (_currentchar != '+' && _currentchar != '-' && !std::isdigit(_currentchar))
		{
			_ErrorReport("after e or E, there must be + or - or number.");
		}

		if (_currentchar == '+' || _currentchar == '-') {
			_AddToBuffer(_currentchar);
			_GetNextChar();
		}

		while (std::isdigit(_currentchar)) {
			_AddToBuffer(_currentchar);
			_GetNextChar();
		}
	}

	void Scanner::_HandleErrorID()
	{
		_AddToBuffer(_currentchar);
		_GetNextChar();

		//todo:
		while (std::isalpha(_currentchar))
		{
			_AddToBuffer(_currentchar);
			_GetNextChar();
		}
	}

	void Scanner::_Preprocess()
	{
		do
		{
			while (std::isspace(_currentchar)) _GetNextChar();

			_HandleLineComment();
			_HandleBlockComment();
		} while (std::isspace(_currentchar));
	}

	void Scanner::_HandleLineComment()
	{
		_loc = _GetTokenLocation();

		if (_currentchar == '/' && _PeekChar() == '/') {
			std::cout << _loc.toString();
			std::cout << "/";
			while (_currentchar != '\n') {
				_GetNextChar();
				std::cout << _currentchar;

				if (_input.eof()) break;
			}

			if (!_input.eof()) _GetNextChar();
		}
	}

	void Scanner::_HandleBlockComment()
	{
		_loc = _GetTokenLocation();

		if (_currentchar == '/' && _PeekChar() == '*') {
			std::cout << _loc.toString();
			std::cout << "/";
			do
			{
				_GetNextChar();
				std::cout << _currentchar;

				if (_input.eof()) {
					_ErrorReport(std::string("end of file happended in comment, */ is expected!"));
					break;
				}
			} while (!(_currentchar == '*' && _PeekChar() == '/'));
			
			if (!_input.eof()) std::cout << "/" << std::endl;

			//eat the '/' after '*'
			_GetNextChar();
			if (!_input.eof()) _GetNextChar();
		}
		
	}

	void Scanner::_ErrorReport(const std::string& msg)
	{
		errorToken(_GetTokenLocation().toString() + msg);
	}

	void Scanner::SetErrorFlag(bool flag)
	{
		_errorFlag = flag;
	}

}