#pragma once

#include <map>
#include <cb/backend/Backend.hpp>
#include <cb/frontend/Frontend.hpp>

namespace cb::backend
{
    class Runtime
    {
    public:
        void AddSymbol(const frontend::SymbolPtr& symbol);
        void MaterializeSymbols();

        std::map<std::string, frontend::SymbolPtr>& GetSymbolMap();
        const frontend::SymbolPtr& GetSymbol(const std::string& name);
        frontend::FunctionSymbolPtr GetFunction(const std::string& name);

    private:
        std::map<std::string, frontend::SymbolPtr> m_Symbols;
    };
}
