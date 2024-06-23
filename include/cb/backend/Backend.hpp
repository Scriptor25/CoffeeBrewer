#pragma once

#include <memory>

namespace cb::backend
{
    struct Function;
    typedef std::shared_ptr<Function> FunctionPtr;

    struct Block;
    typedef std::shared_ptr<Block> BlockPtr;

    struct Instruction;
    typedef std::shared_ptr<Instruction> InstructionPtr;
}
