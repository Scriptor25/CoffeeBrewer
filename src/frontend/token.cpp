#include <cb/frontend/Token.hpp>

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const TokenType& rhs)
{
    switch (rhs)
    {
    case TokenType_EndOfFile: return lhs << "EndOfFile";
    case TokenType_ID: return lhs << "ID";
    case TokenType_Int: return lhs << "Int";
    case TokenType_Float: return lhs << "Float";
    case TokenType_String: return lhs << "String";
    case TokenType_SymbolName: return lhs << "SymbolName";
    case TokenType_RegisterName: return lhs << "RegisterName";
    case TokenType_LabelName: return lhs << "LabelName";
    case TokenType_Equal: return lhs << "Equal";
    case TokenType_Asterisk: return lhs << "Asterisk";
    case TokenType_ParenOpen: return lhs << "ParenOpen";
    case TokenType_ParenClose: return lhs << "ParenClose";
    case TokenType_BraceOpen: return lhs << "BraceOpen";
    case TokenType_BraceClose: return lhs << "BraceClose";
    case TokenType_BracketOpen: return lhs << "BracketOpen";
    case TokenType_BracketClose: return lhs << "BracketClose";
    case TokenType_Comma: return lhs << "Comma";
    default: throw std::runtime_error("not implemented");
    }
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const Token& rhs)
{
    return lhs << rhs.Where << ": " << rhs.Value << " -> " << rhs.Type;
}
