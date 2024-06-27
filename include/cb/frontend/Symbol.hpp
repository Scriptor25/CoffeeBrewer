#pragma once

#include <any>
#include <forward_list>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <cb/backend/Value.hpp>
#include <cb/frontend/Frontend.hpp>
#include <cb/frontend/Instruction.hpp>
#include <cb/frontend/Location.hpp>

#define CONVERT_ARG(ANY_ARG, TYPE, VALUE_TYPE, ARG) if (ANY_ARG.type() == typeid(TYPE)) { ARG = std::make_shared<VALUE_TYPE>(std::any_cast<TYPE>(ANY_ARG)); continue; }

namespace cb::frontend
{
    struct Symbol
    {
        Symbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name);
        virtual ~Symbol();

        virtual void Materialize();

        Location Where;
        TypePtr Type;
        std::map<std::string, std::string> Mods;
        std::string Name;

        void* Address = nullptr;
    };

    struct Block
    {
        std::string Name;
        InstructionPtr Entry;
    };

    struct FunctionSymbol : Symbol
    {
        FunctionSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const std::vector<std::string>& args);

        void Materialize() override;

        BlockPtr GetBlock(const std::string& label);
        backend::ValuePtr Call(std::map<std::string, SymbolPtr>& symbols, const std::vector<backend::ValuePtr>& args);

        template <typename R, typename... A>
        std::function<R(A...)> As(std::map<std::string, SymbolPtr>& symbols)
        {
            return std::function<R(A...)>([this, &symbols](A... temp_args) -> R
            {
                std::vector<std::any> any_args;
                (void)std::initializer_list<int>{(any_args.push_back(temp_args), 0)...};

                std::vector<backend::ValuePtr> args(any_args.size());
                for (size_t i = 0; i < any_args.size(); ++i)
                {
                    const auto& any_arg = any_args[i];
                    CONVERT_ARG(any_arg, bool, backend::Int8Value, args[i]);
                    CONVERT_ARG(any_arg, int8_t, backend::Int8Value, args[i]);
                    CONVERT_ARG(any_arg, int16_t, backend::Int16Value, args[i]);
                    CONVERT_ARG(any_arg, int32_t, backend::Int32Value, args[i]);
                    CONVERT_ARG(any_arg, int64_t, backend::Int64Value, args[i]);
                    CONVERT_ARG(any_arg, float_t, backend::Float32Value, args[i]);
                    CONVERT_ARG(any_arg, double_t, backend::Float64Value, args[i]);
                    CONVERT_ARG(any_arg, void*, backend::PointerValue, args[i]);
                    CONVERT_ARG(any_arg, const void*, backend::ConstPointerValue, args[i]);
                }

                return Call(symbols, args)->As<R>();
            });
        }

        std::vector<std::string> Args;
        std::map<std::string, BlockPtr> Blocks;
        BlockPtr ActiveBlock;
    };

    struct VariableSymbol : Symbol
    {
        VariableSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name, const InstructionPtr& value);

        void Materialize() override;

        InstructionPtr Value;
    };

    struct ProcFunctionSymbol : Symbol
    {
        ProcFunctionSymbol(const TypePtr& type, const std::string& name);

        void Materialize() override;

        [[nodiscard]] backend::ValuePtr Call(const std::vector<backend::ValuePtr>& args) const;
    };

    std::ostream& operator<<(std::ostream& lhs, const SymbolPtr& rhs);
    std::ostream& operator<<(std::ostream& lhs, const FunctionSymbol& rhs);
    std::ostream& operator<<(std::ostream& lhs, const VariableSymbol& rhs);
}
