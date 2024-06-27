#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <cb/frontend/Token.hpp>

namespace cb::frontend
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

        InstructionPtr NextStatement(const FunctionSymbolPtr& parent);
        InstructionPtr NextLabelStatement();
        InstructionPtr NextReturnStatement();
        InstructionPtr NextStoreStatement();
        InstructionPtr NextBranchStatment(const FunctionSymbolPtr& parent);

        InstructionPtr NextExpression(const std::string& reg);

    private:
        std::istream& m_Stream;
        Location m_Location;
        int m_C = -1;

        Token m_Token;
    };
}
