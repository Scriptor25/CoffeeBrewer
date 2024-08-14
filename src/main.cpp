#include <fstream>
#include <iostream>
#include <cb/backend/Runtime.hpp>
#include <cb/frontend/Parser.hpp>
#include <cb/frontend/Symbol.hpp>
#include <cb/frontend/Type.hpp>

cb::backend::Runtime runtime;

int consumer(const cb::frontend::SymbolPtr& symbol)
{
    std::cout << symbol->Where << ':' << std::endl << symbol << std::endl;
    runtime.AddSymbol(symbol);
    return 0;
}

int main()
{
    const std::filesystem::path filename("../examples/fib.cb");

    std::ifstream stream(filename);
    if (!stream)
    {
        std::cerr << "failed to open stream" << std::endl;
        return 1;
    }

    const auto error = cb::frontend::Parser::Parse(filename, stream, consumer);
    stream.close();

    if (error)
    {
        std::cerr << "failed to parse" << std::endl;
        return error;
    }

    {
        const auto symbol = std::make_shared<cb::frontend::ProcFunctionSymbol>(cb::frontend::FunctionType::Get(cb::frontend::Type::GetInt32(), {cb::frontend::PointerType::Get(cb::frontend::Type::GetInt8())}, false), "puts");
        runtime.AddSymbol(symbol);
    }
    {
        const auto symbol = std::make_shared<cb::frontend::ProcFunctionSymbol>(cb::frontend::FunctionType::Get(cb::frontend::Type::GetInt32(), {cb::frontend::PointerType::Get(cb::frontend::Type::GetInt8())}, true), "printf");
        runtime.AddSymbol(symbol);
    }

    runtime.MaterializeSymbols();

    const auto& main_symbol = runtime.GetFunction("main");
    if (!main_symbol)
    {
        std::cerr << "failed to get main function" << std::endl;
        return 1;
    }

    const auto& main_function = main_symbol->As<int, int, const char**>(runtime.GetSymbolMap());
    const char* argv[]{filename.string().c_str()};
    const auto result = main_function(std::size(argv), argv);
    std::cout << "Exit Code " << result << std::endl;

    return 0;
}
