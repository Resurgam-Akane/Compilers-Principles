/*
Author:xuzhu
Date:2016/10/5
main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include "token.h"
#include "dictionary.h"
#include "scanner.h"
#include "SymbolTable.h"

int main()
{
	std::string FileName;
	LexicalAnalysis::SymbolTable table;
	std::cout << "Input the name of the file:";
	std::cin >> FileName;

	try
	{
		LexicalAnalysis::Scanner scanner(FileName);
		scanner.GetNextToken();

		while (scanner.GetToken().GetTokenType() != LexicalAnalysis::TokenType::END_OF_FILE)
		{
//			table.AddTokenToTable(scanner.GetToken().GetTokenName());
			if (scanner.GetErrorFlag() == false) {
				scanner.GetToken().Show();
				table.AddTokenToTable(scanner.GetToken().GetTokenName());
			}
			else scanner.SetErrorFlag(false);
			scanner.GetNextToken();
		}
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
	}

	std::cout << "================================================" << std::endl;

	table.Print();

	return 0;
}