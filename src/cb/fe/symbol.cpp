#include <cb/fe/expression.hpp>
#include <cb/fe/statement.hpp>
#include <cb/fe/symbol.hpp>
#include <cb/fe/type.hpp>

cb::fe::Symbol::Symbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name)
    : Where(where), Type(type), Mods(mods), Name(name)
{
}

cb::fe::Symbol::~Symbol() = default;

std::ostream& cb::fe::operator<<(std::ostream& lhs, const SymbolPtr& rhs)
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

cb::fe::VariableSymbol::VariableSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const ExpressionPtr& value)
    : Symbol(where, type, mods, name), Value(value)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const VariableSymbol& rhs)
{
    return lhs << " = " << rhs.Value;
}

cb::fe::FunctionSymbol::FunctionSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const std::vector<std::string>& args, const std::vector<StatementPtr>& body)
    : Symbol(where, type, mods, name), Args(args), Body(body)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const FunctionSymbol& rhs)
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
