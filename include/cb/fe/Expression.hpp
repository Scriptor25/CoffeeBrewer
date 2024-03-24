#pragma once

#include <cb/Frontend.hpp>

#include <string>
#include <vector>

namespace cb::fe
{
	struct Expression
	{
		Expression(TypePtr type);
		~Expression() = default;

		TypePtr Type;
	};

	struct RegisterExpression : Expression
	{
		static RegisterExpressionPtr Create(TypePtr type, const std::string& name);

		RegisterExpression(TypePtr type, const std::string& name);

		std::string Name;
	};

	struct SymbolExpression : Expression
	{
		static SymbolExpressionPtr Create(TypePtr type, const std::string& name);

		SymbolExpression(TypePtr type, const std::string& name);

		std::string Name;
	};

	struct ConstExpression : Expression
	{
		static ConstExpressionPtr Create(TypePtr type, const std::string& value);

		ConstExpression(TypePtr type, const std::string& value);

		std::string Value;
	};

	struct OperationExpression : Expression
	{
		static OperationExpressionPtr Create(TypePtr type, const std::string& operation, const std::vector<ExpressionPtr>& args);

		OperationExpression(TypePtr type, const std::string& operation, const std::vector<ExpressionPtr>& args);

		std::string Operation;
		std::vector<ExpressionPtr> Args;
	};
}
