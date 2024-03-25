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

	struct Insertable
	{
		virtual ~Insertable() = default;

		virtual void Insert(const StatementPtr& ptr) = 0;
	};

	struct Function : Symbol, Insertable
	{
		static FunctionPtr Create(const std::string& name, FunctionTypePtr type, const std::vector<std::string>& args);

		Function(const std::string& name, FunctionTypePtr type, const std::vector<std::string>& args);

		void Insert(const StatementPtr& ptr);

		std::vector<std::string> Args;
		std::vector<StatementPtr> Body;
		std::vector<LabelPtr> Labels;
	};

	struct Label : Insertable
	{
		static LabelPtr Create(const std::string& name, const FunctionPtr& func);

		Label(const std::string& name, const FunctionPtr& func);

		void Insert(const StatementPtr& ptr);

		std::string Name;
		FunctionPtr Func;
		std::vector<StatementPtr> Body;
	};
}
