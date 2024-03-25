#include <cb/fe/Expression.hpp>
#include <cb/fe/Parser.hpp>
#include <cb/fe/Statement.hpp>
#include <cb/fe/Symbol.hpp>
#include <cb/fe/Type.hpp>

cb::fe::StatementPtr cb::fe::Parser::NextStatement(InsertablePtr& insertable)
{
	if (NextIfAt("%"))
	{
		const auto name = NextName();
		Expect("=");
		const auto initializer = NextExpression();
		return RegisterStatement::Create(name, initializer);
	}

	if (NextIfAt("$"))
	{
		const auto name = NextName();
		Expect(":");

		FunctionPtr func;
		if (const auto f = std::dynamic_pointer_cast<Function>(insertable))
			func = f;
		else if (const auto l = std::dynamic_pointer_cast<Label>(insertable))
			func = l->Func;
		else
			throw std::runtime_error("wtf");

		const auto label = Label::Create(name, func);
		func->Labels.push_back(label);

		insertable = label;
		return NextStatement(insertable);
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

	if (NextIfAt("store"))
	{
		const auto ptr = NextExpression();
		Expect(",");
		const auto value = NextExpression();
		return StoreStatement::Create(ptr, value);
	}

	return NextExpression();
}
