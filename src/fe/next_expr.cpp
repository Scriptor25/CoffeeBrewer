#include <cb/fe/Expression.hpp>
#include <cb/fe/Parser.hpp>

cb::fe::ExpressionPtr cb::fe::Parser::NextExpression()
{
	const auto type = NextType();

	if (NextIfAt("%"))
	{
		const auto name = NextName();
		return RegisterExpression::Create(type, name);
	}

	if (NextIfAt("@"))
	{
		const auto name = NextName();
		return SymbolExpression::Create(type, name);
	}

	if (NextIfAt("const"))
		return ConstExpression::Create(type, Eat().Value);

	const auto operation = Expect(TokenType_Identifier).Value;
	std::vector<ExpressionPtr> args;
	do
	{
		args.push_back(NextExpression());
	} while (NextIfAt(","));

	return OperationExpression::Create(type, operation, args);
}
