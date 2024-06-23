#pragma once

#include <string>
#include <cb/fe/fe.hpp>

namespace cb::fe
{
    struct Type
    {
        static TypePtr Get(const std::string& name);

        explicit Type(const std::string& name);
        virtual ~Type();
    };

    struct PointerType : Type
    {
        static TypePtr Get(const TypePtr& base);

        PointerType(const std::string& name, const TypePtr& base);
    };

    struct FunctionType : Type
    {
        static TypePtr Get(const TypePtr& base, const std::vector<TypePtr>& args);

        FunctionType(const std::string& name, const TypePtr& base, const std::vector<TypePtr>& args);
    };
}
