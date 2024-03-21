#pragma once

#include <cb/Frontend.hpp>

namespace cb::fe
{
    struct Arg
    {
        static ArgPtr Get(TypePtr type) { return std::make_shared<Arg>(type); }

        Arg(TypePtr type)
            : Type(type) {}

        TypePtr Type;
        std::string Name;
    };
}
