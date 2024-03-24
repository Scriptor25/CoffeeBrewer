#pragma once

#include <cb/Frontend.hpp>

#include <string>
#include <vector>

namespace cb::fe
{
	struct Symbol
	{
		Symbol(const std::string& name, TypePtr type);
		virtual ~Symbol() = default;

		std::string Name;
		TypePtr Type;
	};

	struct GlobalVariable : Symbol
	{
		static GlobalVariablePtr Create(const std::string& name, TypePtr type, ExpressionPtr initializer);

		GlobalVariable(const std::string& name, TypePtr type, ExpressionPtr initializer);

		ExpressionPtr Initializer;
	};

	struct Function : Symbol
	{
		static FunctionPtr Create(const std::string& name, FunctionTypePtr type, const std::vector<ArgPtr>& args);
		static FunctionPtr Create(const std::string& name, FunctionTypePtr type, const std::vector<ArgPtr>& args, const std::vector<StatementPtr>& body);

		Function(const std::string& name, FunctionTypePtr type, const std::vector<ArgPtr>& args);
		Function(const std::string& name, FunctionTypePtr type, const std::vector<ArgPtr>& args, const std::vector<StatementPtr>& body);

		std::vector<ArgPtr> Args;
		std::vector<StatementPtr> Body;
	};
}
