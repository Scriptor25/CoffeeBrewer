#include <cb/Frontend.hpp>
#include <cb/fe/Expression.hpp>
#include <cb/fe/Statement.hpp>
#include <cb/fe/Type.hpp>

std::ostream &cb::fe::operator<<(std::ostream &out, const StatementPtr &sptr)
{
    if (const auto p = std::dynamic_pointer_cast<SymbolStatement>(sptr)) return out << *p;
    if (const auto p = std::dynamic_pointer_cast<FunctionDeclaration>(sptr)) return out << *p;

    if (const auto p = std::dynamic_pointer_cast<Expression>(sptr)) return out << p;

    throw std::runtime_error("not yet implemented");
}

std::ostream &cb::fe::operator<<(std::ostream &out, const SymbolStatement &s)
{
    return out << s.Type->Name << " @" << s.Name << " = " << s.Initializer;
}

std::ostream &cb::fe::operator<<(std::ostream &out, const FunctionDeclaration &s)
{
    out << s.Type->Result->Name << " @" << s.Name << "(";
    for (size_t i = 0; i < s.Type->Args.size(); i++)
    {
        if (i > 0) out << ", ";
        out << s.Type->Args[i]->Name;
    }
    return out << ")";
}

std::ostream &cb::fe::operator<<(std::ostream &out, const ExpressionPtr &eptr)
{
    if (const auto p = std::dynamic_pointer_cast<IntExpression>(eptr)) return out << *p;

    throw std::runtime_error("not yet implemented");
}

std::ostream &cb::fe::operator<<(std::ostream &out, const IntExpression &e)
{
    return out << "const " << e.Type->Name << " " << e.Value;
}
