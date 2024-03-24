#include <cb/fe/Arg.hpp>

cb::fe::ArgPtr cb::fe::Arg::Create(TypePtr type)
{
	return std::make_shared<Arg>(type);
}

cb::fe::Arg::Arg(TypePtr type)
	: Type(type)
{
}
