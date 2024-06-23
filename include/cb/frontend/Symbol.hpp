#pragma once

#include <map>
#include <string>
#include <vector>
#include <cb/frontend/Frontend.hpp>
#include <cb/frontend/Location.hpp>

namespace cb::frontend
{
    struct Symbol
    {
        Symbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name);
        virtual ~Symbol();

        Location Where;
        TypePtr Type;
        std::map<std::string, std::string> Mods;
        std::string Name;
    };

    std::ostream& operator<<(std::ostream& lhs, const SymbolPtr& rhs);

    struct VariableSymbol : Symbol
    {
        VariableSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const ExpressionPtr& value);

        ExpressionPtr Value;
    };

    std::ostream& operator<<(std::ostream& lhs, const VariableSymbol& rhs);

    struct FunctionSymbol : Symbol
    {
        FunctionSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const std::vector<std::string>& args, const std::vector<StatementPtr>& body);

        std::vector<std::string> Args;
        std::vector<StatementPtr> Body;
    };

    std::ostream& operator<<(std::ostream& lhs, const FunctionSymbol& rhs);
}
