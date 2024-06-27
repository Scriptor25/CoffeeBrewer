#include <map>
#include <cb/frontend/Type.hpp>

#define INFO_IS_VOID     0b00000001
#define INFO_IS_INTEGER  0b00000010
#define INFO_IS_FLOAT    0b00000100
#define INFO_IS_FUNCTION 0b00001000
#define INFO_IS_POINTER  0b00010000

static std::map<std::string, cb::frontend::TypePtr> Types
{
    {"void", std::make_shared<cb::frontend::Type>(INFO_IS_VOID, "void")},
    {"i8", std::make_shared<cb::frontend::Type>(INFO_IS_INTEGER, "i8")},
    {"i16", std::make_shared<cb::frontend::Type>(INFO_IS_INTEGER, "i16")},
    {"i32", std::make_shared<cb::frontend::Type>(INFO_IS_INTEGER, "i32")},
    {"i64", std::make_shared<cb::frontend::Type>(INFO_IS_INTEGER, "i64")},
    {"f32", std::make_shared<cb::frontend::Type>(INFO_IS_FLOAT, "f32")},
    {"f64", std::make_shared<cb::frontend::Type>(INFO_IS_FLOAT, "f64")},
};

cb::frontend::TypePtr cb::frontend::Type::Get(const std::string& name)
{
    return Get(0, name);
}

cb::frontend::TypePtr cb::frontend::Type::Get(const int info, const std::string& name)
{
    auto& ref = Types[name];
    if (!ref) ref = std::make_shared<Type>(info, name);
    return ref;
}

cb::frontend::TypePtr cb::frontend::Type::GetVoid()
{
    return Get(INFO_IS_VOID, "void");
}

cb::frontend::TypePtr cb::frontend::Type::GetInt8()
{
    return Get(INFO_IS_INTEGER, "i8");
}

cb::frontend::TypePtr cb::frontend::Type::GetInt16()
{
    return Get(INFO_IS_INTEGER, "i16");
}

cb::frontend::TypePtr cb::frontend::Type::GetInt32()
{
    return Get(INFO_IS_INTEGER, "i32");
}

cb::frontend::TypePtr cb::frontend::Type::GetInt64()
{
    return Get(INFO_IS_INTEGER, "i64");
}

cb::frontend::TypePtr cb::frontend::Type::GetFloat32()
{
    return Get(INFO_IS_FLOAT, "f32");
}

cb::frontend::TypePtr cb::frontend::Type::GetFloat64()
{
    return Get(INFO_IS_FLOAT, "f64");
}

cb::frontend::FunctionTypePtr cb::frontend::Type::AsFunction(const TypePtr& type)
{
    return std::dynamic_pointer_cast<FunctionType>(type);
}

cb::frontend::PointerTypePtr cb::frontend::Type::AsPointer(const TypePtr& type)
{
    return std::dynamic_pointer_cast<PointerType>(type);
}

cb::frontend::Type::Type(const int info, const std::string& name)
    : Info(info), Name(name)
{
}

cb::frontend::Type::~Type() = default;

bool cb::frontend::Type::IsVoid() const
{
    return Info & INFO_IS_VOID;
}

bool cb::frontend::Type::IsInteger() const
{
    return Info & INFO_IS_INTEGER;
}

bool cb::frontend::Type::IsFloat() const
{
    return Info & INFO_IS_FLOAT;
}

bool cb::frontend::Type::IsFunction() const
{
    return Info & INFO_IS_FUNCTION;
}

bool cb::frontend::Type::IsPointer() const
{
    return Info & INFO_IS_POINTER;
}

cb::frontend::TypePtr cb::frontend::FunctionType::Get(const TypePtr& base, const std::vector<TypePtr>& args, const bool is_varargs)
{
    auto name = base->Name + '(';
    for (size_t i = 0; i < args.size(); ++i)
    {
        if (i > 0) name += ", ";
        name += args[i]->Name;
    }
    if (is_varargs) name += ", ...";
    name += ')';

    auto& ref = Types[name];
    if (!ref) ref = std::make_shared<FunctionType>(name, base, args, is_varargs);
    return ref;
}

cb::frontend::FunctionType::FunctionType(const std::string& name, const TypePtr& base, const std::vector<TypePtr>& args, const bool is_varargs)
    : Type(INFO_IS_FUNCTION, name), Base(base), Args(args), IsVarargs(is_varargs)
{
}

cb::frontend::TypePtr cb::frontend::PointerType::Get(const TypePtr& base)
{
    auto name = base->Name + '*';

    auto& ref = Types[name];
    if (!ref) ref = std::make_shared<PointerType>(name, base);
    return ref;
}

cb::frontend::PointerType::PointerType(const std::string& name, const TypePtr& base)
    : Type(INFO_IS_POINTER, name), Base(base)
{
}
