#pragma once

#include <cb/Frontend.hpp>

#include <string>
#include <vector>

namespace cb::fe
{
	struct Type
	{
		static TypePtr Create(const std::string& name);

		Type(const std::string& name);

		virtual ~Type() = default;

		std::string Name;
	};

	struct PointerType : Type
	{
		static PointerTypePtr Create(TypePtr base);

		PointerType(TypePtr base);

		TypePtr Base;
	};

	struct ArrayType : Type
	{
		static ArrayTypePtr Create(TypePtr base, size_t size);

		ArrayType(TypePtr base, size_t size);

		TypePtr Base;
		size_t Size;
	};

	struct FunctionType : Type
	{
		static FunctionTypePtr Create(TypePtr result, const std::vector<TypePtr>& args);

		FunctionType(TypePtr result, const std::vector<TypePtr>& args);

		TypePtr Result;
		std::vector<TypePtr> Args;
	};
}
