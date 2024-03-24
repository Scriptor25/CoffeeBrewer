#pragma once

#include <cb/Frontend.hpp>

#include <istream>

namespace cb::fe
{
	struct Token
	{
		Token();
		Token(const size_t line);
		Token(const size_t line, const TokenType type, const char c);
		Token(const size_t line, const TokenType type, const std::string& value);

		size_t Line;
		TokenType Type;
		std::string Value;
	};
}
