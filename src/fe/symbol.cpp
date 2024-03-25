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

cb::fe::FunctionPtr cb::fe::Function::Create(const std::string& name, FunctionTypePtr type, const std::vector<std::string>& args)
{
	return std::make_shared<Function>(name, type, args);
}

cb::fe::Function::Function(const std::string& name, FunctionTypePtr type, const std::vector<std::string>& args)
	: Symbol(name, type), Args(args)
{
}

void cb::fe::Function::Insert(const StatementPtr& ptr)
{
	Body.push_back(ptr);
}

cb::fe::LabelPtr cb::fe::Label::Create(const std::string& name, const FunctionPtr& func)
{
	return std::make_shared<Label>(name, func);
}

cb::fe::Label::Label(const std::string& name, const FunctionPtr& func)
	: Name(name), Func(func)
{
}

void cb::fe::Label::Insert(const StatementPtr& ptr)
{
	Body.push_back(ptr);
}
