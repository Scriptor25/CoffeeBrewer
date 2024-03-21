#pragma once

#include <cb/Frontend.hpp>

#include <string>
#include <vector>

namespace cb::fe
{
    struct Type
    {
        static TypePtr Get(const std::string &name) { return std::make_shared<Type>(name); }

        Type(const std::string &name)
            : Name(name) {}

        virtual ~Type() = default;

        std::string Name;
    };

    struct PointerType : Type
    {
        static PointerTypePtr Get(TypePtr base) { return std::make_shared<PointerType>(base); }

        PointerType(TypePtr base)
            : Type(base->Name + "*"),
              BaseType(base) {}

        TypePtr BaseType;
    };

    struct ArrayType : Type
    {
        static ArrayTypePtr Get(TypePtr base, size_t size) { return std::make_shared<ArrayType>(base, size); }

        ArrayType(TypePtr base, size_t size)
            : Type(base->Name + "[" + std::to_string(size) + "]"),
              BaseType(base),
              Size(size) {}

        TypePtr BaseType;
        size_t Size;
    };

    inline std::string make_function_type_name(const TypePtr &result, const std::vector<TypePtr> &args)
    {
        std::string name = result->Name + "(";
        for (size_t i = 0; i < args.size(); i++)
        {
            if (i > 0) name += ", ";
            name += args[i]->Name;
        }
        return name + ")";
    }

    struct FunctionType : Type
    {
        static FunctionTypePtr Get(TypePtr result, const std::vector<TypePtr> &args)
        {
            return std::make_shared<FunctionType>(result, args);
        }

        FunctionType(TypePtr result, const std::vector<TypePtr> &args)
            : Type(make_function_type_name(result, args)),
              Result(result),
              Args(args) {}

        TypePtr Result;
        std::vector<TypePtr> Args;
    };
}
