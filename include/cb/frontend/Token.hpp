#pragma once

#include <string>
#include <cb/frontend/Frontend.hpp>
#include <cb/frontend/Location.hpp>

namespace cb::frontend
{
    enum TokenType
    {
        TokenType_EndOfFile,
        TokenType_ID,
        TokenType_Int,
        TokenType_Float,
        TokenType_String,
        TokenType_SymbolName,
        TokenType_RegisterName,
        TokenType_LabelName,
        TokenType_Equal,
        TokenType_Comma,
        TokenType_Period,
        TokenType_Colon,
        TokenType_Asterisk,
        TokenType_ParenOpen,
        TokenType_ParenClose,
        TokenType_BraceOpen,
        TokenType_BraceClose,
        TokenType_BracketOpen,
        TokenType_BracketClose,
    };

    std::ostream& operator<<(std::ostream& lhs, const TokenType& rhs);

    struct Token
    {
        Location Where;
        TokenType Type = TokenType_EndOfFile;
        std::string Value;
    };

    std::ostream& operator<<(std::ostream& lhs, const Token& rhs);
}
