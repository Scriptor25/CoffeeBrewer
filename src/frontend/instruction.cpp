#include <cassert>
#include <cmath>
#include <cb/backend/Value.hpp>
#include <cb/frontend/Instruction.hpp>
#include <cb/frontend/Symbol.hpp>
#include <cb/frontend/Type.hpp>

cb::frontend::Instruction::Instruction(const Location& where, const std::string& reg, const TypePtr& type)
    : Where(where), Register(reg), Type(type)
{
}

cb::frontend::Instruction::~Instruction() = default;

void cb::frontend::Instruction::InsertInto(const FunctionSymbolPtr& parent)
{
    Parent = parent;

    if (!parent->ActiveBlock->Entry)
    {
        parent->ActiveBlock->Entry = shared_from_this();
        Prev = nullptr;
    }
    else
    {
        auto ptr = parent->ActiveBlock->Entry;
        while (ptr->Next) ptr = ptr->Next;
        ptr->Next = shared_from_this();
        Prev = ptr;
    }
}

void cb::frontend::Instruction::MaterializeConstant(backend::ValuePtr& reg) const
{
    throw std::runtime_error("not a constant");
}

cb::frontend::AllocaInstruction::AllocaInstruction(const Location& where, const std::string& reg, const TypePtr& type, const TypePtr& element_type, const InstructionPtr& count)
    : Instruction(where, reg, type), ElementType(element_type), Count(count)
{
}

cb::frontend::InstructionPtr cb::frontend::AllocaInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    Count->Run(symbols, registers);
    const auto count = registers["#0"]->AsInt64();

    void* ptr;
    if (ElementType == Type::GetInt8()) ptr = new int8_t[count];
    else if (ElementType == Type::GetInt16()) ptr = new int16_t[count];
    else if (ElementType == Type::GetInt32()) ptr = new int32_t[count];
    else if (ElementType == Type::GetInt64()) ptr = new int64_t[count];
    else if (ElementType == Type::GetFloat32()) ptr = new float_t[count];
    else if (ElementType == Type::GetFloat64()) ptr = new double_t[count];
    else throw std::runtime_error("not implemented");

    registers[Register] = std::make_shared<backend::PointerValue>(ptr);

    return Next;
}

cb::frontend::BranchInstruction::BranchInstruction(const Location& where, const BlockPtr& dest)
    : Instruction(where, "", nullptr), Dest(dest)
{
}

cb::frontend::InstructionPtr cb::frontend::BranchInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    return Dest->Entry;
}

cb::frontend::CallInstruction::CallInstruction(const Location& where, const std::string& reg, const TypePtr& type, const InstructionPtr& callee, const std::vector<InstructionPtr>& args)
    : Instruction(where, reg, type), Callee(callee), Args(args)
{
}

cb::frontend::InstructionPtr cb::frontend::CallInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    Callee->Run(symbols, registers);
    for (const auto& arg : Args)
        arg->Run(symbols, registers);

    const auto callee = static_cast<Symbol*>(registers["#0"]->AsPointer());
    std::vector<backend::ValuePtr> args;
    for (size_t i = 1; i <= Args.size(); ++i)
        args.push_back(registers["#" + std::to_string(i)]);

    if (const auto p = dynamic_cast<FunctionSymbol*>(callee))
        registers[Register] = p->Call(symbols, args);
    if (const auto p = dynamic_cast<ProcFunctionSymbol*>(callee))
        registers[Register] = p->Call(args);

    return Next;
}

cb::frontend::ConditionBranchInstruction::ConditionBranchInstruction(const Location& where, const InstructionPtr& condition, const BlockPtr& dest_then, const BlockPtr& dest_else)
    : Instruction(where, "", nullptr), Condition(condition), DestThen(dest_then), DestElse(dest_else)
{
}

cb::frontend::InstructionPtr cb::frontend::ConditionBranchInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    Condition->Run(symbols, registers);
    if (registers["#0"]->AsBool())
        return DestThen->Entry;
    return DestElse->Entry;
}

cb::frontend::ConstInstruction::ConstInstruction(const Location& where, const std::string& reg, const TypePtr& type, TokenType value_type, const std::string& value)
    : Instruction(where, reg, type), ValueType(value_type), Value(value)
{
}

void cb::frontend::ConstInstruction::MaterializeConstant(backend::ValuePtr& reg) const
{
    void* ptr;
    switch (ValueType)
    {
    case TokenType_Int:
        {
            const auto value = std::stoll(Value);
            if (Type == Type::GetInt8()) ptr = new int8_t(static_cast<int8_t>(value));
            else if (Type == Type::GetInt16()) ptr = new int16_t(static_cast<int16_t>(value));
            else if (Type == Type::GetInt32()) ptr = new int32_t(static_cast<int32_t>(value));
            else if (Type == Type::GetInt64()) ptr = new int64_t(static_cast<int64_t>(value));
            else if (Type == Type::GetFloat32()) ptr = new float_t(static_cast<float_t>(value));
            else if (Type == Type::GetFloat64()) ptr = new double_t(static_cast<double_t>(value));
            break;
        }
    case TokenType_Float:
        {
            const auto value = std::stod(Value);
            if (Type == Type::GetInt8()) ptr = new int8_t(static_cast<int8_t>(value));
            else if (Type == Type::GetInt16()) ptr = new int16_t(static_cast<int16_t>(value));
            else if (Type == Type::GetInt32()) ptr = new int32_t(static_cast<int32_t>(value));
            else if (Type == Type::GetInt64()) ptr = new int64_t(static_cast<int64_t>(value));
            else if (Type == Type::GetFloat32()) ptr = new float_t(static_cast<float_t>(value));
            else if (Type == Type::GetFloat64()) ptr = new double_t(static_cast<double_t>(value));
            break;
        }
    case TokenType_String:
        {
            const auto value = Value.c_str();
            ptr = new const char*(value);
            break;
        }
    default:
        throw std::runtime_error("not implemented");
    }

    reg = std::make_shared<backend::PointerValue>(ptr);
}

cb::frontend::InstructionPtr cb::frontend::ConstInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    auto& reg = registers[Register];
    switch (ValueType)
    {
    case TokenType_Int:
        {
            const auto value = std::stoll(Value);
            if (Type == Type::GetInt8()) reg = std::make_shared<backend::Int8Value>(static_cast<int8_t>(value));
            else if (Type == Type::GetInt16()) reg = std::make_shared<backend::Int16Value>(static_cast<int16_t>(value));
            else if (Type == Type::GetInt32()) reg = std::make_shared<backend::Int32Value>(static_cast<int32_t>(value));
            else if (Type == Type::GetInt64()) reg = std::make_shared<backend::Int64Value>(static_cast<int64_t>(value));
            else if (Type == Type::GetFloat32()) reg = std::make_shared<backend::Float32Value>(static_cast<float_t>(value));
            else if (Type == Type::GetFloat64()) reg = std::make_shared<backend::Float64Value>(static_cast<double_t>(value));
            break;
        }
    case TokenType_Float:
        {
            const auto value = std::stod(Value);
            if (Type == Type::GetInt8()) reg = std::make_shared<backend::Int8Value>(static_cast<int8_t>(value));
            else if (Type == Type::GetInt16()) reg = std::make_shared<backend::Int16Value>(static_cast<int16_t>(value));
            else if (Type == Type::GetInt32()) reg = std::make_shared<backend::Int32Value>(static_cast<int32_t>(value));
            else if (Type == Type::GetInt64()) reg = std::make_shared<backend::Int64Value>(static_cast<int64_t>(value));
            else if (Type == Type::GetFloat32()) reg = std::make_shared<backend::Float32Value>(static_cast<float_t>(value));
            else if (Type == Type::GetFloat64()) reg = std::make_shared<backend::Float64Value>(static_cast<double_t>(value));
            break;
        }
    case TokenType_String:
        {
            reg = std::make_shared<backend::ConstPointerValue>(Value.c_str());
            break;
        }
    default:
        throw std::runtime_error("not implemented");
    }

    return Next;
}

cb::frontend::GetRegisterInstruction::GetRegisterInstruction(const Location& where, const std::string& reg, const TypePtr& type, const std::string& name)
    : Instruction(where, reg, type), Name(name)
{
}

cb::frontend::InstructionPtr cb::frontend::GetRegisterInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    registers[Register] = registers[Name];
    return Next;
}

cb::frontend::LabelInstruction::LabelInstruction(const Location& where, const std::string& name)
    : Instruction(where, "", nullptr), Name(name)
{
}

cb::frontend::InstructionPtr cb::frontend::LabelInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    throw std::runtime_error("not implemented");
}

cb::frontend::LoadInstruction::LoadInstruction(const Location& where, const std::string& reg, const TypePtr& type, const InstructionPtr& base, const InstructionPtr& offset)
    : Instruction(where, reg, type), Base(base), Offset(offset)
{
}

cb::frontend::InstructionPtr cb::frontend::LoadInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    Base->Run(symbols, registers);
    Offset->Run(symbols, registers);

    const auto base = registers["#0"]->AsPointer();
    const auto offset = registers["#1"]->AsInt64();

    auto& reg = registers[Register];

    const auto ptr_base = Type::AsPointer(Base->Type)->Base;
    if (ptr_base == Type::GetInt8()) reg = std::make_shared<backend::Int8Value>(base, offset);
    else if (ptr_base == Type::GetInt16()) reg = std::make_shared<backend::Int16Value>(base, offset);
    else if (ptr_base == Type::GetInt32()) reg = std::make_shared<backend::Int32Value>(base, offset);
    else if (ptr_base == Type::GetInt64()) reg = std::make_shared<backend::Int64Value>(base, offset);
    else if (ptr_base == Type::GetFloat32()) reg = std::make_shared<backend::Float32Value>(base, offset);
    else if (ptr_base == Type::GetFloat64()) reg = std::make_shared<backend::Float64Value>(base, offset);
    else if (ptr_base->IsPointer()) reg = std::make_shared<backend::PointerValue>(base, offset);
    else throw std::runtime_error("not implemented");

    return Next;
}

cb::frontend::OperationInstruction::OperationInstruction(const Location& where, const std::string& reg, const TypePtr& type, const std::string& op, const std::vector<InstructionPtr>& ops)
    : Instruction(where, reg, type), Operator(op), Operands(ops)
{
}

cb::backend::ValuePtr cmp_lt(const cb::frontend::TypePtr& lhs_type, const cb::frontend::TypePtr& rhs_type, const cb::backend::ValuePtr& lhs, const cb::backend::ValuePtr& rhs)
{
    assert(lhs_type == rhs_type);

    if (lhs_type == cb::frontend::Type::GetInt8()) return std::make_shared<cb::backend::Int8Value>(lhs->AsInt8() < rhs->AsInt8());
    if (lhs_type == cb::frontend::Type::GetInt16()) return std::make_shared<cb::backend::Int8Value>(lhs->AsInt16() < rhs->AsInt16());
    if (lhs_type == cb::frontend::Type::GetInt32()) return std::make_shared<cb::backend::Int8Value>(lhs->AsInt32() < rhs->AsInt32());
    if (lhs_type == cb::frontend::Type::GetInt64()) return std::make_shared<cb::backend::Int8Value>(lhs->AsInt64() < rhs->AsInt64());
    if (lhs_type == cb::frontend::Type::GetFloat32()) return std::make_shared<cb::backend::Int8Value>(lhs->AsFloat32() < rhs->AsFloat32());
    if (lhs_type == cb::frontend::Type::GetFloat64()) return std::make_shared<cb::backend::Int8Value>(lhs->AsFloat64() < rhs->AsFloat64());

    throw std::runtime_error("not implemented");
}

cb::backend::ValuePtr add(const cb::frontend::TypePtr& lhs_type, const cb::frontend::TypePtr& rhs_type, const cb::backend::ValuePtr& lhs, const cb::backend::ValuePtr& rhs)
{
    assert(lhs_type == rhs_type);

    if (lhs_type == cb::frontend::Type::GetInt8()) return std::make_shared<cb::backend::Int8Value>(lhs->AsInt8() + rhs->AsInt8());
    if (lhs_type == cb::frontend::Type::GetInt16()) return std::make_shared<cb::backend::Int16Value>(lhs->AsInt16() + rhs->AsInt16());
    if (lhs_type == cb::frontend::Type::GetInt32()) return std::make_shared<cb::backend::Int32Value>(lhs->AsInt32() + rhs->AsInt32());
    if (lhs_type == cb::frontend::Type::GetInt64()) return std::make_shared<cb::backend::Int64Value>(lhs->AsInt64() + rhs->AsInt64());
    if (lhs_type == cb::frontend::Type::GetFloat32()) return std::make_shared<cb::backend::Float32Value>(lhs->AsFloat32() + rhs->AsFloat32());
    if (lhs_type == cb::frontend::Type::GetFloat64()) return std::make_shared<cb::backend::Float64Value>(lhs->AsFloat64() + rhs->AsFloat64());

    throw std::runtime_error("not implemented");
}

cb::frontend::InstructionPtr cb::frontend::OperationInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    for (const auto& operand : Operands)
        operand->Run(symbols, registers);

    auto& reg = registers[Register];
    if (Operator == "cmp_lt") reg = cmp_lt(Operands[0]->Type, Operands[1]->Type, registers["#0"], registers["#1"]);
    else if (Operator == "add") reg = add(Operands[0]->Type, Operands[1]->Type, registers["#0"], registers["#1"]);
    else throw std::runtime_error("not implemented");

    return Next;
}

cb::frontend::ReturnInstruction::ReturnInstruction(const Location& where, const InstructionPtr& value)
    : Instruction(where, "", nullptr), Value(value)
{
}

cb::frontend::InstructionPtr cb::frontend::ReturnInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    if (Value)
    {
        Value->Run(symbols, registers);
        registers[Register] = registers["#0"];
    }
    else
    {
        registers[Register] = nullptr;
    }
    return Next;
}

cb::frontend::StoreInstruction::StoreInstruction(const Location& where, const InstructionPtr& base, const InstructionPtr& offset, const InstructionPtr& value)
    : Instruction(where, "", nullptr), Base(base), Offset(offset), Value(value)
{
}

cb::frontend::InstructionPtr cb::frontend::StoreInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    Base->Run(symbols, registers);
    Offset->Run(symbols, registers);

    const auto base = registers["#0"]->AsPointer();
    const auto offset = registers["#1"]->AsInt64();

    Value->Run(symbols, registers);
    const auto& value = registers["#2"];

    const auto ptr_base = Type::AsPointer(Base->Type)->Base;
    if (ptr_base == Type::GetInt8()) static_cast<int8_t*>(base)[offset] = value->AsInt8();
    else if (ptr_base == Type::GetInt16()) static_cast<int16_t*>(base)[offset] = value->AsInt16();
    else if (ptr_base == Type::GetInt32()) static_cast<int32_t*>(base)[offset] = value->AsInt32();
    else if (ptr_base == Type::GetInt64()) static_cast<int64_t*>(base)[offset] = value->AsInt64();
    else if (ptr_base == Type::GetFloat32()) static_cast<float_t*>(base)[offset] = value->AsFloat32();
    else if (ptr_base == Type::GetFloat64()) static_cast<double_t*>(base)[offset] = value->AsFloat64();
    else throw std::runtime_error("not implemented");

    return Next;
}

cb::frontend::SymbolInstruction::SymbolInstruction(const Location& where, const std::string& reg, const TypePtr& type, const std::string& name)
    : Instruction(where, reg, type), Name(name)
{
}

cb::frontend::InstructionPtr cb::frontend::SymbolInstruction::Run(std::map<std::string, SymbolPtr>& symbols, std::map<std::string, backend::ValuePtr>& registers) const
{
    registers[Register] = std::make_shared<backend::PointerValue>(symbols[Name]->Address);
    return Next;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const InstructionPtr& rhs)
{
    if (!rhs->Register.empty() && rhs->Register[0] != '#')
        lhs << '%' << rhs->Register << " = ";
    if (rhs->Type)
        lhs << rhs->Type->Name << ' ';

    if (const auto p = std::dynamic_pointer_cast<AllocaInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<BranchInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<CallInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<ConditionBranchInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<ConstInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<GetRegisterInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<LabelInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<LoadInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<OperationInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<ReturnInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<StoreInstruction>(rhs)) return lhs << *p;
    if (const auto p = std::dynamic_pointer_cast<SymbolInstruction>(rhs)) return lhs << *p;

    throw std::runtime_error("not implemented");
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const AllocaInstruction& rhs)
{
    return lhs << "alloca " << rhs.ElementType->Name << ", " << rhs.Count;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const BranchInstruction& rhs)
{
    return lhs << "br $" << rhs.Dest->Name;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const CallInstruction& rhs)
{
    lhs << "call " << rhs.Callee;
    for (const auto& arg : rhs.Args)
        lhs << ", " << arg;
    return lhs;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const ConditionBranchInstruction& rhs)
{
    return lhs << "br " << rhs.Condition << ", $" << rhs.DestThen->Name << ", $" << rhs.DestElse->Name;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const ConstInstruction& rhs)
{
    return lhs << "const " << rhs.Value;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const GetRegisterInstruction& rhs)
{
    return lhs << '%' << rhs.Name;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const LabelInstruction& rhs)
{
    return lhs << '$' << rhs.Name << ':';
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const LoadInstruction& rhs)
{
    return lhs << "load " << rhs.Base << ", " << rhs.Offset;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const OperationInstruction& rhs)
{
    lhs << "op " << rhs.Operator;
    for (const auto& op : rhs.Operands)
        lhs << ", " << op;
    return lhs;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const ReturnInstruction& rhs)
{
    lhs << "ret ";
    if (rhs.Value) return lhs << rhs.Value;
    return lhs << "void";
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const StoreInstruction& rhs)
{
    return lhs << "store " << rhs.Base << ", " << rhs.Offset << ", " << rhs.Value;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const SymbolInstruction& rhs)
{
    return lhs << '@' << rhs.Name;
}
