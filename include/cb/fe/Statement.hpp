#pragma once

#include <cb/Frontend.hpp>

#include <string>
#include <vector>

namespace cb::fe
{
	struct Statement
	{
		virtual ~Statement() = default;
	};

	struct RegisterStatement : Statement
	{
		static RegisterStatementPtr Create(const std::string& name, ExpressionPtr initializer);

		RegisterStatement(const std::string& name, ExpressionPtr initializer);

		std::string Name;
		ExpressionPtr Initializer;
	};

	struct ReturnStatement : Statement
	{
		static ReturnStatementPtr Create(ExpressionPtr value);

		ReturnStatement(ExpressionPtr value);

		ExpressionPtr Value;
	};

	struct BranchStatement : Statement
	{
		static BranchStatementPtr Create(ExpressionPtr index, const std::vector<std::string>& labels);

		BranchStatement(ExpressionPtr index, const std::vector<std::string>& labels);

		ExpressionPtr Index;
		std::vector<std::string> Labels;
	};
}
