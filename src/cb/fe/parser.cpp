#include <iostream>
#include <vector>
#include <cb/fe/parser.hpp>
#include <cb/fe/type.hpp>

int cb::fe::Parser::Parse(const std::filesystem::path& filename, std::istream& stream)
{
    Parser parser(filename, stream);

    for (parser.NextToken(); !parser.AtEOF(); parser.NextToken())
        std::cout << parser.m_Token << std::endl;

    return 0;
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

bool cb::fe::Parser::SkipIfAt(const TokenType type)
{
    if (!At(type))
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

cb::fe::TypePtr cb::fe::Parser::NextType()
{
    TypePtr base;

    while (true)
    {
        if (base)
        {
            if (SkipIfAt(TokenType_Asterisk))
            {
                base = PointerType::Get(base);
                continue;
            }

            if (SkipIfAt(TokenType_ParenOpen))
            {
                std::vector<TypePtr> args;
                while (!AtEOF() && !At(TokenType_ParenClose))
                {
                    args.push_back(NextType());
                    if (!At(TokenType_ParenClose))
                        Expect(TokenType_Comma);
                }
                Expect(TokenType_ParenClose);

                base = FunctionType::Get(base, args);
                continue;
            }

            return base;
        }

        const auto name = Expect(TokenType_ID).Value;
        base = Type::Get(name);
    }
}
