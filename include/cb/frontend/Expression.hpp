#pragma once

#include <vector>
#include <cb/frontend/Frontend.hpp>
#include <cb/frontend/Statement.hpp>
#include <cb/frontend/Token.hpp>

namespace cb::frontend
{
    struct Expression : Statement
    {
        Expression(const Location& where, const TypePtr& type);

        TypePtr Type;
    };

    std::ostream& operator<<(std::ostream& lhs, const ExpressionPtr& rhs);

    struct SymbolExpression : Expression
    {
        SymbolExpression(const Location& where, const TypePtr& type, const std::string& name);

        std::string Name;
    };

    std::ostream& operator<<(std::ostream& lhs, const SymbolExpression& rhs);

    struct RegisterExpression : Expression
    {
        RegisterExpression(const Location& where, const TypePtr& type, const std::string& name);

        std::string Name;
    };

    std::ostream& operator<<(std::ostream& lhs, const RegisterExpression& rhs);

    struct ConstExpression : Expression
    {
        ConstExpression(const Location& where, const TypePtr& type, TokenType value_type, const std::string& value);

        TokenType ValueType;
        std::string Value;
    };

    std::ostream& operator<<(std::ostream& lhs, const ConstExpression& rhs);

    struct LoadExpression : Expression
    {
        LoadExpression(const Location& where, const TypePtr& type, const ExpressionPtr& base, const ExpressionPtr& offset);

        ExpressionPtr Base;
        ExpressionPtr Offset;
    };

    std::ostream& operator<<(std::ostream& lhs, const LoadExpression& rhs);

    struct CallExpression : Expression
    {
        CallExpression(const Location& where, const TypePtr& type, const ExpressionPtr& callee, const std::vector<ExpressionPtr>& args);

        ExpressionPtr Callee;
        std::vector<ExpressionPtr> Args;
    };

    std::ostream& operator<<(std::ostream& lhs, const CallExpression& rhs);

    struct AllocaExpression : Expression
    {
        AllocaExpression(const Location& where, const TypePtr& type, const TypePtr& element_type, const ExpressionPtr& count);

        TypePtr ElementType;
        ExpressionPtr Count;
    };

    std::ostream& operator<<(std::ostream& lhs, const AllocaExpression& rhs);

    struct OperationExpression : Expression
    {
        OperationExpression(const Location& where, const TypePtr& type, const std::string& op, const std::vector<ExpressionPtr>& ops);

        std::string Operator;
        std::vector<ExpressionPtr> Operands;
    };

    std::ostream& operator<<(std::ostream& lhs, const OperationExpression& rhs);
}
