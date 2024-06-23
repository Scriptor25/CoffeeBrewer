#pragma once

#include <vector>
#include <cb/backend/Backend.hpp>

namespace cb::backend
{
    struct Function
    {
        BlockPtr Entry;
        std::vector<BlockPtr> Blocks;
    };
}
