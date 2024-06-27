#pragma once

#include <map>
#include <vector>
#include <cb/backend/Backend.hpp>
#include <cb/frontend/Frontend.hpp>
#include <cb/frontend/Location.hpp>
#include <cb/frontend/Token.hpp>

namespace cb::frontend
{
    struct Instruction : std::enable_shared_from_this<Instruction>
    {
        explicit Instruction(const Location& where, const std::string& reg, const TypePtr& type);
        virtual ~Instruction();

        void InsertInto(const FunctionSymbolPtr& parent);

        virtual void MaterializeConstant(backend::ValuePtr& reg) const;
        virtual InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const = 0;

        Location Where;

        std::string Register;
        TypePtr Type;
        FunctionSymbolPtr Parent;
        InstructionPtr Prev;
        InstructionPtr Next;
    };

    struct AllocaInstruction : Instruction
    {
        AllocaInstruction(const Location& where, const std::string& reg, const TypePtr& type, const TypePtr& element_type, const InstructionPtr& count);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        TypePtr ElementType;
        InstructionPtr Count;
    };

    struct BranchInstruction : Instruction
    {
        BranchInstruction(const Location& where, const BlockPtr& dest);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        BlockPtr Dest;
    };

    struct CallInstruction : Instruction
    {
        CallInstruction(const Location& where, const std::string& reg, const TypePtr& type, const InstructionPtr& callee, const std::vector<InstructionPtr>& args);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        InstructionPtr Callee;
        std::vector<InstructionPtr> Args;
    };

    struct ConditionBranchInstruction : Instruction
    {
        ConditionBranchInstruction(const Location& where, const InstructionPtr& condition, const BlockPtr& dest_then, const BlockPtr& dest_else);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        InstructionPtr Condition;
        BlockPtr DestThen;
        BlockPtr DestElse;
    };

    struct ConstInstruction : Instruction
    {
        ConstInstruction(const Location& where, const std::string& reg, const TypePtr& type, TokenType value_type, const std::string& value);

        void MaterializeConstant(backend::ValuePtr& reg) const override;
        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        TokenType ValueType;
        std::string Value;
    };

    struct GetRegisterInstruction : Instruction
    {
        GetRegisterInstruction(const Location& where, const std::string& reg, const TypePtr& type, const std::string& name);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        std::string Name;
    };

    struct LabelInstruction : Instruction
    {
        LabelInstruction(const Location& where, const std::string& name);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        std::string Name;
    };

    struct LoadInstruction : Instruction
    {
        LoadInstruction(const Location& where, const std::string& reg, const TypePtr& type, const InstructionPtr& base, const InstructionPtr& offset);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        InstructionPtr Base;
        InstructionPtr Offset;
    };

    struct OperationInstruction : Instruction
    {
        OperationInstruction(const Location& where, const std::string& reg, const TypePtr& type, const std::string& op, const std::vector<InstructionPtr>& ops);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        std::string Operator;
        std::vector<InstructionPtr> Operands;
    };

    struct ReturnInstruction : Instruction
    {
        explicit ReturnInstruction(const Location& where, const InstructionPtr& value = nullptr);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        InstructionPtr Value;
    };

    struct StoreInstruction : Instruction
    {
        StoreInstruction(const Location& where, const InstructionPtr& base, const InstructionPtr& offset, const InstructionPtr& value);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        InstructionPtr Base;
        InstructionPtr Offset;
        InstructionPtr Value;
    };

    struct SymbolInstruction : Instruction
    {
        SymbolInstruction(const Location& where, const std::string& reg, const TypePtr& type, const std::string& name);

        InstructionPtr Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const override;

        std::string Name;
    };

    std::ostream& operator<<(std::ostream& lhs, const InstructionPtr& rhs);
    std::ostream& operator<<(std::ostream& lhs, const AllocaInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const BranchInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const CallInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const ConditionBranchInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const ConstInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const LabelInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const LoadInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const OperationInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const GetRegisterInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const ReturnInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const StoreInstruction& rhs);
    std::ostream& operator<<(std::ostream& lhs, const SymbolInstruction& rhs);
}
