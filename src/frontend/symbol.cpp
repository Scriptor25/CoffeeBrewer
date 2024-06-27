#include <cassert>
#include <cb/frontend/Instruction.hpp>
#include <cb/frontend/Symbol.hpp>
#include <cb/frontend/Type.hpp>

cb::frontend::Symbol::Symbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name)
    : Where(where), Type(type), Mods(mods), Name(name)
{
}

cb::frontend::Symbol::~Symbol() = default;

void cb::frontend::Symbol::Materialize()
{
    Address = nullptr;
}

cb::frontend::FunctionSymbol::FunctionSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const std::vector<std::string>& args)
    : Symbol(where, type, mods, name), Args(args), ActiveBlock(Blocks[""] = std::make_shared<Block>("", nullptr))
{
}

void cb::frontend::FunctionSymbol::Materialize()
{
    Address = this;
}

cb::frontend::BlockPtr cb::frontend::FunctionSymbol::GetBlock(const std::string& label)
{
    auto& block = Blocks[label];
    if (!block) block = std::make_shared<Block>(label, nullptr);
    return block;
}

cb::backend::ValuePtr cb::frontend::FunctionSymbol::Call(std::map<std::string, SymbolPtr>& symbols, const std::vector<backend::ValuePtr>& args)
{
    const auto& entry_block = Blocks[""];

    std::map<std::string, backend::ValuePtr> registers;
    for (size_t i = 0; i < Args.size(); ++i)
        registers[Args[i]] = args[i];

    for (auto ptr = entry_block->Entry; ptr;)
        ptr = ptr->Run(symbols, registers);

    return registers[""];
}

cb::frontend::VariableSymbol::VariableSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const InstructionPtr& value)
    : Symbol(where, type, mods, name), Value(value)
{
}

void cb::frontend::VariableSymbol::Materialize()
{
    backend::ValuePtr reg;
    Value->MaterializeConstant(reg);
    Address = reg->AsPointer();
}

cb::frontend::ProcFunctionSymbol::ProcFunctionSymbol(const TypePtr& type, const std::string& name)
    : Symbol({}, type, {}, name)
{
}

void cb::frontend::ProcFunctionSymbol::Materialize()
{
    Address = this;
}

cb::backend::ValuePtr cb::frontend::ProcFunctionSymbol::Call(const std::vector<backend::ValuePtr>& args) const
{
    if (Name == "puts")
    {
        const auto str = static_cast<const char*>(args[0]->AsConstPointer());
        return std::make_shared<backend::Int32Value>(puts(str));
    }

    throw std::runtime_error("not implemented");
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const SymbolPtr& rhs)
{
    lhs << rhs->Type->Name << ' ';
    if (!rhs->Mods.empty())
    {
        lhs << '[';
        size_t i = 0;
        for (const auto& [key, value] : rhs->Mods)
        {
            if (i > 0) lhs << ", ";
            lhs << key << '=' << value;
            ++i;
        }
        lhs << "] ";
    }
    lhs << '@' << rhs->Name;

    if (const auto p = std::dynamic_pointer_cast<VariableSymbol>(rhs))
        return lhs << *p;

    if (const auto p = std::dynamic_pointer_cast<FunctionSymbol>(rhs))
        return lhs << *p;

    return lhs;
}

size_t spacing_count = 0;

std::string get_spacing()
{
    std::string spacing;
    for (size_t i = 0; i < spacing_count; ++i)
        spacing += "    ";
    return spacing;
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const FunctionSymbol& rhs)
{
    lhs << '(';
    for (size_t i = 0; i < rhs.Args.size(); ++i)
    {
        if (i > 0) lhs << ", ";
        lhs << '%' << rhs.Args[i];
    }
    lhs << ')' << std::endl << '{' << std::endl;

    const auto spacing0 = get_spacing();
    ++spacing_count;
    const auto spacing1 = get_spacing();

    for (const auto& [name, block] : rhs.Blocks)
    {
        if (!name.empty())
            lhs << std::endl << spacing0 << '$' << name << ':' << std::endl;
        for (auto ptr = block->Entry; ptr; ptr = ptr->Next)
            lhs << spacing1 << ptr << std::endl;
    }

    --spacing_count;

    return lhs << '}';
}

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const VariableSymbol& rhs)
{
    return lhs << " = " << rhs.Value;
}
