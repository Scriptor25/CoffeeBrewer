#include <cb/fe/expression.hpp>
#include <cb/fe/statement.hpp>

cb::fe::Statement::Statement(const Location& where)
    : Where(where)
{
}

cb::fe::Statement::~Statement() = default;

std::ostream& cb::fe::operator<<(std::ostream& lhs, const StatementPtr& rhs)
{
    if (const auto p = std::dynamic_pointer_cast<Expression>(rhs))
        return lhs << p;

    if (const auto p = std::dynamic_pointer_cast<RegisterStatement>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<LabelStatement>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<ReturnStatement>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<StoreStatement>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<BranchStatement>(rhs))
        return lhs << *p;

    throw std::runtime_error("not implemented");
}

cb::fe::RegisterStatement::RegisterStatement(const Location& where, const std::string& name, const ExpressionPtr& value)
    : Statement(where), Name(name), Value(value)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const RegisterStatement& rhs)
{
    return lhs << '%' << rhs.Name << " = " << rhs.Value;
}

cb::fe::LabelStatement::LabelStatement(const Location& where, const std::string& name)
    : Statement(where), Name(name)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const LabelStatement& rhs)
{
    return lhs << '$' << rhs.Name << ':';
}

cb::fe::ReturnStatement::ReturnStatement(const Location& where, const ExpressionPtr& value)
    : Statement(where), Value(value)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const ReturnStatement& rhs)
{
    lhs << "ret ";
    if (rhs.Value) return lhs << rhs.Value;
    return lhs << "void";
}

cb::fe::StoreStatement::StoreStatement(const Location& where, const ExpressionPtr& base, const ExpressionPtr& offset, const ExpressionPtr& value)
    : Statement(where), Base(base), Offset(offset), Value(value)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const StoreStatement& rhs)
{
    return lhs << "store " << rhs.Base << ", " << rhs.Offset << ", " << rhs.Value;
}

cb::fe::BranchStatement::BranchStatement(const Location& where, const ExpressionPtr& condition, const std::string& destination)
    : Statement(where), Condition(condition), Destination(destination)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const BranchStatement& rhs)
{
    return lhs << "br " << rhs.Condition << ", $" << rhs.Destination;
}
