#include <cb/fe/Expression.hpp>
#include <cb/fe/Parser.hpp>
#include <cb/fe/Statement.hpp>
#include <cb/fe/Type.hpp>

cb::fe::StatementPtr cb::fe::Parser::NextStatement()
{
	if (NextIfAt("%"))
	{
		const auto name = NextName();
		Expect("=");
		const auto initializer = NextExpression();
		return RegisterStatement::Create(name, initializer);
	}

	if (NextIfAt("$")) // TODO
	{
		const auto name = NextName();
		Expect(":");
		return nullptr;
	}

	if (NextIfAt("ret"))
	{
		const auto value = NextExpression();
		return ReturnStatement::Create(value);
	}

	if (NextIfAt("br"))
	{
		const auto index = NextExpression();
		std::vector<std::string> labels;
		Expect(",");
		do
		{
			Expect("$");
			const auto label = NextName();
			labels.push_back(label);
		} while (NextIfAt(","));
		return BranchStatement::Create(index, labels);
	}

	throw std::runtime_error("not yet implemented");
}
