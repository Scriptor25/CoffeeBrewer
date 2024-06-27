#pragma once

#include <memory>

namespace cb::frontend
{
    struct Location;
    struct Token;

    class Parser;

    struct Type;
    struct FunctionType;
    struct PointerType;

    typedef std::shared_ptr<Type> TypePtr;
    typedef std::shared_ptr<FunctionType> FunctionTypePtr;
    typedef std::shared_ptr<PointerType> PointerTypePtr;

    struct Symbol;
    struct Block;
    struct FunctionSymbol;
    struct VariableSymbol;

    struct Instruction;
    struct AllocaInstruction;
    struct BranchInstruction;
    struct CallInstruction;
    struct ConditionBranchInstruction;
    struct ConstInstruction;
    struct GetRegisterInstruction;
    struct LabelInstruction;
    struct LoadInstruction;
    struct OperationInstruction;
    struct ReturnInstruction;
    struct StoreInstruction;
    struct SymbolInstruction;

    typedef std::shared_ptr<Symbol> SymbolPtr;
    typedef std::shared_ptr<Block> BlockPtr;
    typedef std::shared_ptr<FunctionSymbol> FunctionSymbolPtr;
    typedef std::shared_ptr<Instruction> InstructionPtr;
}
