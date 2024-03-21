#pragma once

#include <cb/Frontend.hpp>

#include <string>
#include <vector>

namespace cb::fe
{
    struct Statement
    {
        virtual ~Statement() = default;
    };

    struct FunctionDeclaration : Statement
    {
        static FunctionDeclarationPtr Get(const std::string &name, FunctionTypePtr type)
        {
            return std::make_shared<FunctionDeclaration>(name, type);
        }

        FunctionDeclaration(const std::string &name, FunctionTypePtr type)
            : Name(name), Type(type) {}

        std::string Name;
        FunctionTypePtr Type;
    };

    struct FunctionDefinition : FunctionDeclaration
    {
        static FunctionDefinitionPtr Get(const std::string &name, FunctionTypePtr type,
                                         const std::vector<std::string> &argnames)
        {
            return std::make_shared<FunctionDefinition>(name, type, argnames);
        }

        FunctionDefinition(const std::string &name, FunctionTypePtr type, const std::vector<std::string> &argnames)
            : FunctionDeclaration(name, type), ArgNames(argnames) {}

        std::vector<std::string> ArgNames;
    };

    struct ReturnStatement : Statement
    {
        ExpressionPtr Result;
    };

    struct BreakStatement : Statement
    {
        ExpressionPtr Switch;
        std::vector<LabelPtr> Labels;
    };

    struct SymbolStatement : Statement
    {
        static SymbolStatementPtr Get(const std::string &name, TypePtr type, ExpressionPtr initializer)
        {
            return std::make_shared<SymbolStatement>(name, type, initializer);
        }

        SymbolStatement(const std::string &name, TypePtr type, ExpressionPtr initializer)
            : Name(name), Type(type), Initializer(initializer) {}

        std::string Name;
        TypePtr Type;
        ExpressionPtr Initializer;
    };

    struct RegisterStatement : Statement
    {
        std::string Name;
        ExpressionPtr Initializer;
    };
}
