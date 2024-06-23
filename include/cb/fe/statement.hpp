#pragma once

#include <cb/fe/fe.hpp>
#include <cb/fe/location.hpp>

namespace cb::fe
{
    struct Statement
    {
        explicit Statement(const Location& where);
        virtual ~Statement();

        Location Where;
    };

    std::ostream& operator<<(std::ostream& lhs, const StatementPtr& rhs);

    struct RegisterStatement : Statement
    {
        RegisterStatement(const Location& where, const std::string& name, const ExpressionPtr& value);

        std::string Name;
        ExpressionPtr Value;
    };

    std::ostream& operator<<(std::ostream& lhs, const RegisterStatement& rhs);

    struct LabelStatement : Statement
    {
        LabelStatement(const Location& where, const std::string& name);

        std::string Name;
    };

    std::ostream& operator<<(std::ostream& lhs, const LabelStatement& rhs);

    struct ReturnStatement : Statement
    {
        ReturnStatement(const Location& where, const ExpressionPtr& value);

        ExpressionPtr Value;
    };

    std::ostream& operator<<(std::ostream& lhs, const ReturnStatement& rhs);

    struct StoreStatement : Statement
    {
        StoreStatement(const Location& where, const ExpressionPtr& base, const ExpressionPtr& offset, const ExpressionPtr& value);

        ExpressionPtr Base;
        ExpressionPtr Offset;
        ExpressionPtr Value;
    };

    std::ostream& operator<<(std::ostream& lhs, const StoreStatement& rhs);

    struct BranchStatement : Statement
    {
        BranchStatement(const Location& where, const ExpressionPtr& condition, const std::string& destination);

        ExpressionPtr Condition;
        std::string Destination;
    };

    std::ostream& operator<<(std::ostream& lhs, const BranchStatement& rhs);
}
