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
	{
		const auto token = Eat();
		ConstType cnsttype;
		switch (token.Type)
		{
		case TokenType_Integer:
			cnsttype = ConstType_Integer;
			break;
		case TokenType_Float:
			cnsttype = ConstType_Float;
			break;
		case TokenType_Char:
			cnsttype = ConstType_Char;
			break;
		case TokenType_String:
			cnsttype = ConstType_String;
			break;
		default:
			throw std::runtime_error("unexpected type");
		}
		return ConstExpression::Create(type, token.Value, cnsttype);
	}

	const auto operation = Expect(TokenType_Identifier).Value;
	std::vector<ExpressionPtr> args;
	do
	{
		args.push_back(NextExpression());
	} while (NextIfAt(","));

	return OperationExpression::Create(type, operation, args);
}
