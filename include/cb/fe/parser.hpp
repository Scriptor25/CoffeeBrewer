#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <cb/fe/token.hpp>

namespace cb::fe
{
    typedef std::function<int(const SymbolPtr& symbol)> SymbolConsumer;

    class Parser
    {
    public:
        static int Parse(const std::filesystem::path& filename, std::istream& stream, const SymbolConsumer& consumer);

    private:
        explicit Parser(const std::filesystem::path& filename, std::istream& stream);

        int NextChar();
        Token& NextToken();

        [[nodiscard]] bool AtEOF() const;
        [[nodiscard]] bool At(TokenType type) const;
        [[nodiscard]] bool At(const std::string& value) const;
        bool SkipIfAt(TokenType type);
        bool SkipIfAt(const std::string& value);
        Token Expect(TokenType type);
        void Expect(const std::string& value);

        TypePtr NextType();

        SymbolPtr NextSymbol();
        SymbolPtr NextVariableSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name);
        SymbolPtr NextFunctionSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name);

        StatementPtr NextStatement();
        StatementPtr NextRegisterStatement();
        StatementPtr NextLabelStatement();
        StatementPtr NextReturnStatement();
        StatementPtr NextStoreStatement();
        StatementPtr NextBranchStatment();

        ExpressionPtr NextExpression();

    private:
        std::istream& m_Stream;
        Location m_Location;
        int m_C = -1;

        Token m_Token;
    };
}
