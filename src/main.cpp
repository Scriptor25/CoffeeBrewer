#include <fstream>
#include <iostream>
#include <cb/fe/parser.hpp>

int main()
{
    std::ifstream stream("../examples/fib.cb");
    if (!stream)
    {
        std::cerr << "failed to open stream" << std::endl;
        return 1;
    }

    if (const auto error = cb::fe::Parser::Parse("examples/fib.cb", stream))
    {
        std::cerr << "failed to parse" << std::endl;
        return error;
    }

    stream.close();
}
