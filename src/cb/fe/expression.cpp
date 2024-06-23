#include <cb/fe/expression.hpp>
#include <cb/fe/type.hpp>

cb::fe::Expression::Expression(const Location& where, const TypePtr& type)
    : Statement(where), Type(type)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const ExpressionPtr& rhs)
{
    lhs << rhs->Type->Name << ' ';

    if (const auto p = std::dynamic_pointer_cast<SymbolExpression>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<RegisterExpression>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<ConstExpression>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<LoadExpression>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<CallExpression>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<AllocaExpression>(rhs))
        return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<OperationExpression>(rhs))
        return lhs << *p;

    throw std::runtime_error("not implemented");
}

cb::fe::SymbolExpression::SymbolExpression(const Location& where, const TypePtr& type, const std::string& name)
    : Expression(where, type), Name(name)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const SymbolExpression& rhs)
{
    return lhs << '@' << rhs.Name;
}

cb::fe::RegisterExpression::RegisterExpression(const Location& where, const TypePtr& type, const std::string& name)
    : Expression(where, type), Name(name)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const RegisterExpression& rhs)
{
    return lhs << '%' << rhs.Name;
}

cb::fe::ConstExpression::ConstExpression(const Location& where, const TypePtr& type, TokenType value_type, const std::string& value)
    : Expression(where, type), ValueType(value_type), Value(value)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const ConstExpression& rhs)
{
    return lhs << "const " << rhs.Value;
}

cb::fe::LoadExpression::LoadExpression(const Location& where, const TypePtr& type, const ExpressionPtr& base, const ExpressionPtr& offset)
    : Expression(where, type), Base(base), Offset(offset)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const LoadExpression& rhs)
{
    return lhs << "load " << rhs.Base << ", " << rhs.Offset;
}

cb::fe::CallExpression::CallExpression(const Location& where, const TypePtr& type, const ExpressionPtr& callee, const std::vector<ExpressionPtr>& args)
    : Expression(where, type), Callee(callee), Args(args)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const CallExpression& rhs)
{
    lhs << "call " << rhs.Callee;
    for (const auto& arg : rhs.Args)
        lhs << ", " << arg;
    return lhs;
}

cb::fe::AllocaExpression::AllocaExpression(const Location& where, const TypePtr& type, const TypePtr& element_type, const ExpressionPtr& count)
    : Expression(where, type), ElementType(element_type), Count(count)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const AllocaExpression& rhs)
{
    return lhs << "alloca " << rhs.ElementType->Name << ", " << rhs.Count;
}

cb::fe::OperationExpression::OperationExpression(const Location& where, const TypePtr& type, const std::string& op, const std::vector<ExpressionPtr>& ops)
    : Expression(where, type), Operator(op), Operands(ops)
{
}

std::ostream& cb::fe::operator<<(std::ostream& lhs, const OperationExpression& rhs)
{
    lhs << "op " << rhs.Operator;
    for (const auto& op : rhs.Operands)
        lhs << ", " << op;
    return lhs;
}
