#include <cb/frontend/Parser.hpp>
#include <cb/frontend/Symbol.hpp>

int cb::frontend::Parser::Parse(const std::filesystem::path& filename, std::istream& stream, const SymbolConsumer& consumer)
{
    Parser parser(filename, stream);

    int error = 0;
    for (parser.NextToken(); !parser.AtEOF();)
        error |= consumer(parser.NextSymbol());

    return error;
}

cb::frontend::Parser::Parser(const std::filesystem::path& filename, std::istream& stream)
    : m_Stream(stream), m_Location{.Filename = filename, .Row = 1, .Column = 0}
{
}

bool cb::frontend::Parser::AtEOF() const
{
    return m_Token.Type == TokenType_EndOfFile;
}

bool cb::frontend::Parser::At(const TokenType type) const
{
    return m_Token.Type == type;
}

bool cb::frontend::Parser::At(const std::string& value) const
{
    return m_Token.Value == value;
}

bool cb::frontend::Parser::SkipIfAt(const TokenType type)
{
    if (!At(type))
        return false;

    NextToken();
    return true;
}

bool cb::frontend::Parser::SkipIfAt(const std::string& value)
{
    if (!At(value))
        return false;

    NextToken();
    return true;
}

cb::frontend::Token cb::frontend::Parser::Expect(const TokenType type)
{
    if (!At(type))
        throw std::runtime_error("unexpected token type");

    auto token = m_Token;
    NextToken();
    return token;
}

void cb::frontend::Parser::Expect(const std::string& value)
{
    if (!At(value))
        throw std::runtime_error("unexpected token value");

    NextToken();
}
