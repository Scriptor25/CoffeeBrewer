#include <cb/fe/Parser.hpp>

int cb::fe::Parser::Get()
{
	auto c = m_Stream.get();
	if (m_Marked)
		m_Buffer.push_back(c);
	return c;
}

void cb::fe::Parser::Mark()
{
	m_Marked = true;
	m_Buffer.clear();
}

void cb::fe::Parser::Reset()
{
	if (!m_Marked)
		throw std::runtime_error("cannot reset if not marked");

	m_Marked = false;
	while (!m_Buffer.empty())
	{
		const auto c = m_Buffer.back();
		m_Stream.putback(static_cast<char>(c));
		m_Buffer.pop_back();
	}
}

int escape(const int c)
{
	switch (c)
	{
	case 'a': return '\a';
	case 'b': return '\b';
	case 'f': return '\f';
	case 'n': return '\n';
	case 'r': return '\r';
	case 't': return '\t';
	case 'v': return '\v';
	default: return c;
	}
}

cb::fe::Token& cb::fe::Parser::Next()
{
	auto c = Get();
	while (c >= 0x00 && c <= 0x20)
	{
		if (c == '\n') m_Line++;
		c = Get();
	}
	if (c < 0x00) return m_Token = Token(m_Line);

	if (c == '"')
	{
		std::string value;
		c = Get();
		while (c != '"' && c >= 0x00)
		{
			if (c == '\\')
				c = escape(Get());
			value += static_cast<char>(c);
			c = Get();
		}

		return m_Token = Token(m_Line, TokenType_String, value);
	}

	if (c == '\'')
	{
		std::string value;
		c = Get();
		while (c != '\'' && c >= 0x00)
		{
			if (c == '\\')
				c = escape(Get());
			value += static_cast<char>(c);
			c = Get();
		}

		return m_Token = Token(m_Line, TokenType_Char, value);
	}

	if (isdigit(c))
	{
		std::string value;
		bool floating = false;
		do
		{
			if (c == '.') floating = true;
			value += static_cast<char>(c);
			Mark();
			c = Get();
		} while (isdigit(c) || c == '.');
		Reset();

		return m_Token = Token(m_Line, floating ? TokenType_Float : TokenType_Integer, value);
	}

	if (isalpha(c) || c == '_')
	{
		std::string value;
		do
		{
			value += static_cast<char>(c);
			Mark();
			c = Get();
		} while (isalnum(c) || c == '_');
		Reset();

		return m_Token = Token(m_Line, TokenType_Identifier, value);
	}

	return m_Token = Token(m_Line, TokenType_Other, static_cast<char>(c));
}

bool cb::fe::Parser::AtEOF() const
{
	return m_Token.Type & TokenType_EOF;
}

bool cb::fe::Parser::At(const std::string& value) const
{
	return m_Token.Value == value;
}

bool cb::fe::Parser::At(const uint32_t type) const
{
	return m_Token.Type & type;
}

bool cb::fe::Parser::NextIfAt(const std::string& value)
{
	if (At(value))
	{
		Next();
		return true;
	}
	return false;
}

void cb::fe::Parser::Expect(const std::string& value)
{
	if (!At(value))
		throw std::runtime_error("unexpected value");
	Next();
}

cb::fe::Token cb::fe::Parser::Expect(const uint32_t type)
{
	if (!At(type))
		throw std::runtime_error("unexpected type");
	return Eat();
}

cb::fe::Token cb::fe::Parser::Eat()
{
	const auto tk = m_Token;
	Next();
	return tk;
}
