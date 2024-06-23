#include <fstream>
#include <iostream>
#include <cb/frontend/Parser.hpp>
#include <cb/frontend/Symbol.hpp>

int consumer(const cb::frontend::SymbolPtr& symbol)
{
    std::cout << symbol->Where << ':' << std::endl << symbol << std::endl;

    // TODO: flatten AST into instruction list (similar to assembly)

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

    if (error) std::cerr << "failed to parse" << std::endl;
    // else TODO: call main/entry point function

    return error;
}
