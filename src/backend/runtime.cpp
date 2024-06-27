#include <cb/backend/Runtime.hpp>
#include <cb/frontend/Symbol.hpp>

void cb::backend::Runtime::AddSymbol(const frontend::SymbolPtr& symbol)
{
    if (auto& ref = m_Symbols[symbol->Name]; !ref || typeid(*ref) == typeid(frontend::Symbol))
        ref = symbol;
}

void cb::backend::Runtime::MaterializeSymbols()
{
    for (const auto& [name, symbol] : m_Symbols)
        symbol->Materialize();
}

std::map<std::string, cb::frontend::SymbolPtr>& cb::backend::Runtime::GetSymbolMap()
{
    return m_Symbols;
}

const cb::frontend::SymbolPtr& cb::backend::Runtime::GetSymbol(const std::string& name)
{
    return m_Symbols[name];
}

cb::frontend::FunctionSymbolPtr cb::backend::Runtime::GetFunction(const std::string& name)
{
    return std::dynamic_pointer_cast<frontend::FunctionSymbol>(m_Symbols[name]);
}
