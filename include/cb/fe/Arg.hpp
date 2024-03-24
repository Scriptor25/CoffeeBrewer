#pragma once

#include <cb/Frontend.hpp>

#include <string>

namespace cb::fe
{
	struct Arg
	{
		static ArgPtr Create(TypePtr type);

		Arg(TypePtr type);

		TypePtr Type;
		std::string Name;
	};
}
