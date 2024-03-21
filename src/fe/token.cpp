#include <cb/fe/Parser.hpp>

std::ostream &cb::fe::operator<<(std::ostream &out, const TokenType &type)
{
    switch (type)
    {
        case TokenType_Char: return out << "chr";
        case TokenType_Float: return out << "flt";
        case TokenType_Identifier: return out << "idt";
        case TokenType_Integer: return out << "int";
        case TokenType_Other: return out << "otr";
        case TokenType_String: return out << "str";
        case TokenType_EOF: return out << "eof";
        default: return out << "UNDEFINED";
    }
}

std::ostream &cb::fe::operator<<(std::ostream &out, const Token &token)
{
    return out
           << "{ line: " << token.Line
           << ", type: " << token.Type
           << ", value: " << token.Value
           << " }";
}
