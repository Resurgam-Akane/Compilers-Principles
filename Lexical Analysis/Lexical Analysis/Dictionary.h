#pragma once
/*
Author:xuzhu
Date:2016/10/4
Dic
*/

#include <string>
#include <tuple>
#include <map>
#include "Token.h"

namespace LexicalAnalysis
{
	class Dictionary
	{
	public:
		Dictionary();
		// find or match keywords
		std::tuple<TokenType, TokenValue, int> Lookup(const std::string& name) const;
		// is the token in dic
		bool HaveToken(const std::string& name) const;

	private:
		void _AddToken(std::string name, std::tuple<TokenValue, TokenType, int> tokenMeta);
		std::map<std::string, std::tuple<TokenValue, TokenType, int>> _dictionary;

	};
}