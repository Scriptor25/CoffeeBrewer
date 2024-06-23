#include <cb/fe/parser.hpp>
#include <cb/fe/symbol.hpp>

int cb::fe::Parser::Parse(const std::filesystem::path& filename, std::istream& stream, const SymbolConsumer& consumer)
{
    Parser parser(filename, stream);

    int error = 0;
    for (parser.NextToken(); !parser.AtEOF();)
        error |= consumer(parser.NextSymbol());

    return error;
}

cb::fe::Parser::Parser(const std::filesystem::path& filename, std::istream& stream)
    : m_Stream(stream), m_Location{.Filename = filename, .Row = 1, .Column = 0}
{
}

bool cb::fe::Parser::AtEOF() const
{
    return m_Token.Type == TokenType_EndOfFile;
}

bool cb::fe::Parser::At(const TokenType type) const
{
    return m_Token.Type == type;
}

bool cb::fe::Parser::At(const std::string& value) const
{
    return m_Token.Value == value;
}

bool cb::fe::Parser::SkipIfAt(const TokenType type)
{
    if (!At(type))
        return false;

    NextToken();
    return true;
}

bool cb::fe::Parser::SkipIfAt(const std::string& value)
{
    if (!At(value))
        return false;

    NextToken();
    return true;
}

cb::fe::Token cb::fe::Parser::Expect(const TokenType type)
{
    if (!At(type))
        throw std::runtime_error("unexpected token type");

    auto token = m_Token;
    NextToken();
    return token;
}

void cb::fe::Parser::Expect(const std::string& value)
{
    if (!At(value))
        throw std::runtime_error("unexpected token value");

    NextToken();
}
