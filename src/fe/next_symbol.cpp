#include <cb/fe/Parser.hpp>
#include <cb/fe/Symbol.hpp>
#include <cb/fe/Type.hpp>

cb::fe::SymbolPtr cb::fe::Parser::NextSymbol()
{
	const auto type = NextType();
	Expect("@");
	const auto name = NextName();

	if (At("=")) return NextGlobalVariable(name, type);

	if (const auto funtype = std::dynamic_pointer_cast<FunctionType>(type))
		return NextFunction(name, funtype);

	throw std::runtime_error("not yet implemented");
}

cb::fe::GlobalVariablePtr cb::fe::Parser::NextGlobalVariable(const std::string& name, TypePtr type)
{
	Expect("=");
	const auto initializer = NextExpression();
	return GlobalVariable::Create(name, type, initializer);
}

cb::fe::FunctionPtr cb::fe::Parser::NextFunction(const std::string& name, FunctionTypePtr type)
{
	std::vector<std::string> args;

	if (NextIfAt("("))
	{
		while (!At(")") && !AtEOF())
		{
			Expect("%");
			const auto arg = NextName();
			args.push_back(arg);

			if (!At(")"))
				Expect(",");
		}
		Expect(")");
	}
	else
	{
		for (size_t i = 0; i < type->Args.size(); i++)
			args.push_back("arg" + std::to_string(i));
	}

	auto function = Function::Create(name, type, args);
	if (!NextIfAt("{"))
		return function;

	InsertablePtr insertable = function;
	while (!At("}") && !AtEOF())
	{
		const auto statement = NextStatement(insertable);
		insertable->Insert(statement);
	}
	Expect("}");

	return function;
}
