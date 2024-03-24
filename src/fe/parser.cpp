#include <cb/fe/Parser.hpp>
#include <cb/fe/Symbol.hpp>

#include <iostream>

bool cb::fe::Parser::Parse(std::istream& stream)
{
	if (!stream)
		return false;

	Parser parser(stream);
	for (parser.Next(); !parser.AtEOF();)
	{
		auto sptr = parser.NextSymbol();
		std::cout << sptr << std::endl;
	}

	return true;
}

cb::fe::Parser::Parser(std::istream& stream)
	: m_Stream(stream)
{
}

std::string cb::fe::Parser::NextName()
{
	return Expect(
		TokenType_Identifier
		| TokenType_Integer
		| TokenType_String
		| TokenType_Char).Value;
}
