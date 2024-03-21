#pragma once

#include <memory>

namespace cb::fe
{
    class Parser;

    struct Statement;
    struct FunctionDeclaration;
    struct FunctionDefinition;
    struct ReturnStatement;
    struct BreakStatement;
    struct SymbolStatement;
    struct RegisterStatement;

    struct Arg;

    struct Expression;

    enum ExpressionType
    {
        ExpressionType_,
        ExpressionType_Call,
        ExpressionType_Const,
        ExpressionType_ICmpEQ,
        ExpressionType_ICmpLE,
        ExpressionType_ISub,
        ExpressionType_IAdd,
    };

    struct Label;

    struct Type;
    struct PointerType;
    struct ArrayType;
    struct FunctionType;

    typedef std::shared_ptr<Statement> StatementPtr;
    typedef std::shared_ptr<FunctionDeclaration> FunctionDeclarationPtr;
    typedef std::shared_ptr<FunctionDefinition> FunctionDefinitionPtr;
    typedef std::shared_ptr<ReturnStatement> ReturnStatementPtr;
    typedef std::shared_ptr<BreakStatement> BreakStatementPtr;
    typedef std::shared_ptr<SymbolStatement> SymbolStatementPtr;
    typedef std::shared_ptr<RegisterStatement> RegisterStatementPtr;

    typedef std::shared_ptr<Arg> ArgPtr;

    typedef std::shared_ptr<Expression> ExpressionPtr;

    typedef std::shared_ptr<Label> LabelPtr;

    typedef std::shared_ptr<Type> TypePtr;
    typedef std::shared_ptr<PointerType> PointerTypePtr;
    typedef std::shared_ptr<ArrayType> ArrayTypePtr;
    typedef std::shared_ptr<FunctionType> FunctionTypePtr;
}
