#pragma once

#include <string>
#include <vector>
#include <cb/frontend/Frontend.hpp>

namespace cb::frontend
{
    struct Type
    {
        static TypePtr Get(const std::string& name);
        static TypePtr Get(int info, const std::string& name);

        static TypePtr GetVoid();
        static TypePtr GetInt8();
        static TypePtr GetInt16();
        static TypePtr GetInt32();
        static TypePtr GetInt64();
        static TypePtr GetFloat32();
        static TypePtr GetFloat64();

        static FunctionTypePtr AsFunction(const TypePtr& type);
        static PointerTypePtr AsPointer(const TypePtr& type);

        Type(int info, const std::string& name);
        virtual ~Type();

        [[nodiscard]] bool IsVoid() const;
        [[nodiscard]] bool IsInteger() const;
        [[nodiscard]] bool IsFloat() const;
        [[nodiscard]] bool IsFunction() const;
        [[nodiscard]] bool IsPointer() const;

        int Info;
        std::string Name;
    };

    struct FunctionType : Type
    {
        static TypePtr Get(const TypePtr& base, const std::vector<TypePtr>& args, bool is_varargs);

        FunctionType(const std::string& name, const TypePtr& base, const std::vector<TypePtr>& args, bool is_varargs);

        TypePtr Base;
        std::vector<TypePtr> Args;
        bool IsVarargs;
    };

    struct PointerType : Type
    {
        static TypePtr Get(const TypePtr& base);

        PointerType(const std::string& name, const TypePtr& base);

        TypePtr Base;
    };
}
