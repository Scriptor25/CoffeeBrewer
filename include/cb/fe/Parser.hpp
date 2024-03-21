#pragma once

#include <cb/Frontend.hpp>

#include <istream>
#include <vector>

namespace cb::fe
{
    enum TokenType
    {
        TokenType_,
        TokenType_EOF,
        TokenType_Identifier,
        TokenType_Integer,
        TokenType_Float,
        TokenType_String,
        TokenType_Char,
        TokenType_Other,
    };

    struct Token
    {
        Token()
            : Line(0), Type(TokenType_EOF) {}

        Token(size_t line, bool unused)
            : Line(line), Type(TokenType_EOF) {}

        Token(size_t line, TokenType type, const std::string &value)
            : Line(line), Type(type), Value(value) {}

        Token(size_t line, TokenType type, char c)
            : Line(line), Type(type), Value(1, c) {}

        size_t Line;
        TokenType Type;
        std::string Value;
    };

    std::ostream &operator<<(std::ostream &out, const TokenType &type);

    std::ostream &operator<<(std::ostream &out, const Token &token);

    class Parser
    {
    public:
        static bool Parse(std::istream &stream);

    private:
        Parser(std::istream &stream);

        int Get();

        void Mark();

        void Reset();

        Token &Next();

        bool AtEOF() const;

        bool At(const std::string &value) const;

        bool At(TokenType type) const;

        bool NextIfAt(const std::string &value);

        void Expect(const std::string &value);

        Token Expect(TokenType type);

        StatementPtr NextStatement();

        FunctionDeclarationPtr NextFunctionDeclaration(TypePtr type, const std::string &name);

        FunctionDefinitionPtr NextFunctionDefinition(FunctionTypePtr type, const std::string &name,
                                                     const std::vector<ArgPtr> &args);

        ReturnStatementPtr NextReturnStatement();

        BreakStatementPtr NextBreakStatement();

        SymbolStatementPtr NextSymbolStatement(TypePtr type, const std::string &name);

        RegisterStatementPtr NextRegisterStatement();

        ExpressionPtr NextExpression();

        LabelPtr NextLabel();

        TypePtr NextType();

        TypePtr NextType(TypePtr base);

        FunctionTypePtr NextFunctionType();

        std::istream &m_Stream;
        bool m_Marked = false;
        std::vector<int> m_Buffer;
        size_t m_Line = 1;
        Token m_Token;
    };
}
