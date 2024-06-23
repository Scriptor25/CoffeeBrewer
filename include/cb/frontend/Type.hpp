#pragma once

#include <string>
#include <vector>
#include <cb/frontend/Frontend.hpp>

namespace cb::frontend
{
    struct Type
    {
        static TypePtr Get(const std::string& name);

        explicit Type(const std::string& name);
        virtual ~Type();

        std::string Name;
    };

    struct PointerType : Type
    {
        static TypePtr Get(const TypePtr& base);

        PointerType(const std::string& name, const TypePtr& base);

        TypePtr Base;
    };

    struct FunctionType : Type
    {
        static TypePtr Get(const TypePtr& base, const std::vector<TypePtr>& args, bool is_varargs);

        FunctionType(const std::string& name, const TypePtr& base, const std::vector<TypePtr>& args, bool is_varargs);

        TypePtr Base;
        std::vector<TypePtr> Args;
        bool IsVarargs;
    };
}
