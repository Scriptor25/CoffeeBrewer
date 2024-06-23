#pragma once

#include <cb/backend/Backend.hpp>

namespace cb::backend
{
    /**
     * An instruction does always have
     *  - a pointer to its parent block
     *  - one or none pointer to an instruction referencing it
     *  - one or none pointer to an instruction it references
     */
    struct Instruction
    {
        virtual ~Instruction();

        BlockPtr Parent;
        InstructionPtr Prev;
        InstructionPtr Next;
    };
}
