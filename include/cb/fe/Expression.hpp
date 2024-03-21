#pragma once

#include <cb/Frontend.hpp>
#include <cb/fe/Statement.hpp>

#include <vector>

namespace cb::fe
{
    struct Expression : Statement
    {
        Expression(ExpressionType type)
            : ExprType(type) {}

        ExpressionType ExprType;
    };

    struct ConstExpression : Expression
    {
        ConstExpression(TypePtr type)
            : Expression(ExpressionType_Const), Type(type) {}

        TypePtr Type;
    };

    struct IntExpression : ConstExpression
    {
        static IntExpressionPtr Get(TypePtr type, int value) { return std::make_shared<IntExpression>(type, value); }

        IntExpression(TypePtr type, int value)
            : ConstExpression(type), Value(value) {}

        int Value;
    };

    struct FloatExpression : ConstExpression
    {
        static FloatExpressionPtr Get(TypePtr type, float value)
        {
            return std::make_shared<FloatExpression>(type, value);
        }

        FloatExpression(TypePtr type, float value)
            : ConstExpression(type), Value(value) {}

        float Value;
    };

    struct CharExpression : ConstExpression
    {
        static CharExpressionPtr Get(TypePtr type, char value) { return std::make_shared<CharExpression>(type, value); }

        CharExpression(TypePtr type, char value)
            : ConstExpression(type), Value(value) {}

        char Value;
    };

    struct StringExpression : ConstExpression
    {
        static StringExpressionPtr Get(TypePtr type, const std::string &value)
        {
            return std::make_shared<StringExpression>(type, value);
        }

        StringExpression(TypePtr type, const std::string &value)
            : ConstExpression(type), Value(value) {}

        std::string Value;
    };

    struct FullExpression : Expression
    {
        FullExpression(ExpressionType type, const std::vector<ExpressionPtr> &args)
            : Expression(type), Args(args) {}

        std::vector<ExpressionPtr> Args;
    };
}
