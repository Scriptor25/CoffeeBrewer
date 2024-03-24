#include <cb/fe/Arg.hpp>
#include <cb/fe/Parser.hpp>
#include <cb/fe/Symbol.hpp>
#include <cb/fe/Type.hpp>

cb::fe::SymbolPtr cb::fe::Parser::NextSymbol()
{
	const auto type = NextType();
	Expect("@");
	const auto name = Expect(TokenType_Identifier).Value;
	if (At("=")) return NextGlobalVariable(name, type);
	if (At("(")) return NextFunction(name, type);

	throw std::runtime_error("unexpected token");
}

cb::fe::GlobalVariablePtr cb::fe::Parser::NextGlobalVariable(const std::string& name, TypePtr type)
{
	Expect("=");
	const auto initializer = NextExpression();
	return GlobalVariable::Create(name, type, initializer);
}

cb::fe::FunctionPtr cb::fe::Parser::NextFunction(const std::string& name, TypePtr result)
{
	std::vector<ArgPtr> args;
	std::vector<TypePtr> argtypes;

	Expect("(");
	while (!At(")") && !AtEOF())
	{
		const auto atype = NextType();
		argtypes.push_back(atype);

		auto arg = Arg::Create(atype);
		args.push_back(arg);

		if (NextIfAt("%"))
			arg->Name = NextName();
		else
			arg->Name = "arg" + std::to_string(args.size() - 1);

		if (!At(")"))
			Expect(",");
	}
	Expect(")");

	const auto type = FunctionType::Create(result, argtypes);

	if (!NextIfAt("{"))
		return Function::Create(name, type, args);

	std::vector<StatementPtr> statements;
	while (!At("}") && !AtEOF())
		statements.push_back(NextStatement());
	Expect("}");

	return Function::Create(name, type, args, statements);
}
