#include "SymbolTable.h"
#include <iostream>

namespace LexicalAnalysis
{
	void SymbolTable::AddTokenToTable(std::string name)
	{
		auto iter = _Table.find(name);
		if (iter != _Table.end()) ++_Table.at(name);
		else _Table[name] = 1;
	}

	void SymbolTable::Print()
	{
		for (auto iter : _Table)
			std::cout << "the token " << iter.first << "\t" << "occur(s) " << iter.second << "\t" << "time(s). " << std::endl;
	}
}