#pragma once

#include <memory>

namespace cb::frontend
{
    struct Location;
    struct Token;
    class Parser;

    struct Type;
    struct PointerType;
    struct FunctionType;
    typedef std::shared_ptr<Type> TypePtr;

    struct Symbol;
    struct VariableSymbol;
    struct FunctionSymbol;
    typedef std::shared_ptr<Symbol> SymbolPtr;

    struct Statement;
    struct RegisterStatement;
    struct LabelStatement;
    struct ReturnStatement;
    struct StoreStatement;
    typedef std::shared_ptr<Statement> StatementPtr;

    struct Expression;
    struct SymbolExpression;
    struct RegisterExpression;
    struct ConstExpression;
    struct LoadExpression;
    struct CallExpression;
    struct AllocaExpression;
    typedef std::shared_ptr<Expression> ExpressionPtr;
}
