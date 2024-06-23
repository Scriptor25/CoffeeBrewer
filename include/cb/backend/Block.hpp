#pragma once

#include <vector>
#include <cb/backend/Backend.hpp>

namespace cb::backend
{
    /**
     * A block does always have
     *  - a pointer to its parent function
     *  - a pointer to its entry instruction
     *  - a pointer to its terminator instruction (br, ret)
     *  - [0; infintiy] pointers to blocks referencing it
     *  - one or none pointer to a referenced block
     */
    struct Block
    {
        FunctionPtr Parent;
        InstructionPtr Entry;
        InstructionPtr Terminator;
        std::vector<BlockPtr> Prev;
        BlockPtr Next;
    };
}
