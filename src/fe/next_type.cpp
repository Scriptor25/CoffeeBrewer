#include <cb/fe/Parser.hpp>
#include <cb/fe/Type.hpp>

cb::fe::TypePtr cb::fe::Parser::NextType()
{
	const auto name = Expect(TokenType_Identifier).Value;
	const auto base = Type::Create(name);
	return NextType(base);
}

cb::fe::TypePtr cb::fe::Parser::NextType(TypePtr base)
{
	if (NextIfAt("*")) return NextType(PointerType::Create(base));
	if (NextIfAt("["))
	{
		const auto size = std::stoull(Expect(TokenType_Integer).Value);
		Expect("]");
		return NextType(ArrayType::Create(base, size));
	}
	if (NextIfAt("("))
	{
		std::vector<TypePtr> args;
		while (!At(")") && !AtEOF())
		{
			const auto type = NextType();
			args.push_back(type);

			if (!At(")"))
				Expect(",");
		}
		Expect(")");
		return NextType(FunctionType::Create(base, args));
	}
	return base;
}
