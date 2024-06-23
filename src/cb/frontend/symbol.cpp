#include <cb/frontend/Expression.hpp>
#include <cb/frontend/Statement.hpp>
#include <cb/frontend/Symbol.hpp>
#include <cb/frontend/Type.hpp>

cb::frontend::Symbol::Symbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name)
    : Where(where), Type(type), Mods(mods), Name(name)
{
}

cb::frontend::Symbol::~Symbol() = default;

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const SymbolPtr& rhs)
{
    lhs << rhs->Type->Name << ' ';
    if (!rhs->Mods.empty())
    {
        lhs << '[';
        size_t i = 0;
        for (const auto& [key, value] : rhs->Mods)
        {
            if (i > 0) lhs << ", ";
            lhs << key << '=' << value;
            ++i;
        }
        lhs << "] ";
    }
    lhs << '@' << rhs->Name;

    if (const auto p = std::dynamic_pointer_cast<VariableSymbol>(rhs))
        return lhs << *p;

    if (const auto p = std::dynamic_pointer_cast<FunctionSymbol>(rhs))
        return lhs << *p;

    return lhs;
}

cb::frontend::VariableSymbol::VariableSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const ExpressionPtr& value)
    : Symbol(where, type, mods, name), Value(value)
{
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const VariableSymbol& rhs)
{
    return lhs << " = " << rhs.Value;
}

cb::frontend::FunctionSymbol::FunctionSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const std::vector<std::string>& args, const std::vector<StatementPtr>& body)
    : Symbol(where, type, mods, name), Args(args), Body(body)
{
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const FunctionSymbol& rhs)
{
    lhs << '(';
    for (size_t i = 0; i < rhs.Args.size(); ++i)
    {
        if (i > 0) lhs << ", ";
        lhs << '%' << rhs.Args[i];
    }
    lhs << ')' << std::endl << '{' << std::endl;
    for (const auto& statement : rhs.Body)
        lhs << statement << std::endl;
    return lhs << '}';
}
