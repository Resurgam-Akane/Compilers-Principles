/*
Author:xuzhu
Date:2016/10/4
Lexical unit
*/
#include <iostream>
#include "Error.h"
#include "Scanner.h"

namespace LexicalAnalysis
{
	void errorToken(const std::string& msg)
	{
		std::cerr << "Token Error:" << msg << std::endl;
		Scanner::SetErrorFlag(true);
	}
}