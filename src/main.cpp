#include <cb/CoffeeBrewer.hpp>
#include <cb/fe/Parser.hpp>

#include <fstream>

int main(int argc, char **argv)
{
    std::ifstream stream("res/hello.cb");
    if (!cb::fe::Parser::Parse(stream))
        return 1;
    return 0;
}
