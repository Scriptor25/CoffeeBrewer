#pragma once

#include <cb/Frontend.hpp>
#include <cb/fe/Statement.hpp>

#include <vector>

namespace cb::fe
{
    struct Expression : Statement
    {
        ExpressionType Type;
        std::vector<ExpressionPtr> Args;
    };
}
