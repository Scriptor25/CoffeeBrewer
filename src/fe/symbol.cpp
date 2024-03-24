#include <cb/fe/Symbol.hpp>
#include <cb/fe/Type.hpp>

cb::fe::Symbol::Symbol(const std::string& name, TypePtr type)
	: Name(name), Type(type)
{
}

cb::fe::GlobalVariablePtr cb::fe::GlobalVariable::Create(const std::string& name, TypePtr type, ExpressionPtr initializer)
{
	return std::make_shared<GlobalVariable>(name, type, initializer);
}

cb::fe::GlobalVariable::GlobalVariable(const std::string& name, TypePtr type, ExpressionPtr initializer)
	: Symbol(name, type), Initializer(initializer)
{
}

cb::fe::FunctionPtr cb::fe::Function::Create(const std::string& name, FunctionTypePtr type, const std::vector<ArgPtr>& args)
{
	return std::make_shared<Function>(name, type, args);
}

cb::fe::FunctionPtr cb::fe::Function::Create(const std::string& name, FunctionTypePtr type, const std::vector<ArgPtr>& args, const std::vector<StatementPtr>& body)
{
	return std::make_shared<Function>(name, type, args, body);
}

cb::fe::Function::Function(const std::string& name, FunctionTypePtr type, const std::vector<ArgPtr>& args)
	: Function(name, type, args, {})
{
}

cb::fe::Function::Function(const std::string& name, FunctionTypePtr type, const std::vector<ArgPtr>& args, const std::vector<StatementPtr>& body)
	: Symbol(name, type), Args(args), Body(body)
{
}
