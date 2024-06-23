#include <map>
#include <cb/fe/type.hpp>

static std::map<std::string, cb::fe::TypePtr> Types;

cb::fe::TypePtr cb::fe::Type::Get(const std::string& name)
{
    auto& ref = Types[name];
    if (!ref) ref = std::make_shared<Type>(name);
    return ref;
}

cb::fe::Type::Type(const std::string& name)
    : Name(name)
{
}

cb::fe::Type::~Type() = default;

cb::fe::TypePtr cb::fe::PointerType::Get(const TypePtr& base)
{
    auto name = base->Name + '*';

    auto& ref = Types[name];
    if (!ref) ref = std::make_shared<PointerType>(name, base);
    return ref;
}

cb::fe::PointerType::PointerType(const std::string& name, const TypePtr& base)
    : Type(name), Base(base)
{
}

cb::fe::TypePtr cb::fe::FunctionType::Get(const TypePtr& base, const std::vector<TypePtr>& args, const bool is_varargs)
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

cb::fe::FunctionType::FunctionType(const std::string& name, const TypePtr& base, const std::vector<TypePtr>& args, const bool is_varargs)
    : Type(name), Base(base), Args(args), IsVarargs(is_varargs)
{
}
