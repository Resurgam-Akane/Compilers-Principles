#pragma once

#include <map>
#include <string>

namespace LexicalAnalysis
{
	class SymbolTable
	{
	public:
//		SymbolTable();
		void AddTokenToTable(std::string name);
		void Print();

	private:
		std::map<std::string, unsigned int> _Table;
	};
}
