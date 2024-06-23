#include <map>
#include <cb/frontend/Type.hpp>

static std::map<std::string, cb::frontend::TypePtr> Types;

cb::frontend::TypePtr cb::frontend::Type::Get(const std::string& name)
{
    auto& ref = Types[name];
    if (!ref) ref = std::make_shared<Type>(name);
    return ref;
}

cb::frontend::Type::Type(const std::string& name)
    : Name(name)
{
}

cb::frontend::Type::~Type() = default;

cb::frontend::TypePtr cb::frontend::PointerType::Get(const TypePtr& base)
{
    auto name = base->Name + '*';

    auto& ref = Types[name];
    if (!ref) ref = std::make_shared<PointerType>(name, base);
    return ref;
}

cb::frontend::PointerType::PointerType(const std::string& name, const TypePtr& base)
    : Type(name), Base(base)
{
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
    : Type(name), Base(base), Args(args), IsVarargs(is_varargs)
{
}
