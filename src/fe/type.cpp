#include <cb/fe/Type.hpp>

cb::fe::TypePtr cb::fe::Type::Create(const std::string& name)
{
	return std::make_shared<Type>(name);
}

cb::fe::Type::Type(const std::string& name)
	: Name(name)
{
}

cb::fe::PointerTypePtr cb::fe::PointerType::Create(TypePtr base)
{
	return std::make_shared<PointerType>(base);
}

cb::fe::PointerType::PointerType(TypePtr base)
	: Type(base->Name + "*"), Base(base)
{
}

cb::fe::ArrayTypePtr cb::fe::ArrayType::Create(TypePtr base, size_t size)
{
	return std::make_shared<ArrayType>(base, size);
}

cb::fe::ArrayType::ArrayType(TypePtr base, size_t size)
	: Type(base->Name + "[" + std::to_string(size) + "]"), Base(base), Size(size)
{
}

cb::fe::FunctionTypePtr cb::fe::FunctionType::Create(TypePtr result, const std::vector<TypePtr>& args)
{
	return std::make_shared<FunctionType>(result, args);
}

std::string make_function_type_name(const cb::fe::TypePtr& result, const std::vector<cb::fe::TypePtr>& args)
{
	std::string name = result->Name + "(";
	for (size_t i = 0; i < args.size(); i++)
	{
		if (i > 0) name += ", ";
		name += args[i]->Name;
	}
	return name + ")";
}

cb::fe::FunctionType::FunctionType(TypePtr result, const std::vector<TypePtr>& args)
	: Type(make_function_type_name(result, args)), Result(result), Args(args)
{
}
