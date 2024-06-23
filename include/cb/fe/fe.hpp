#pragma once

#include <memory>

namespace cb::fe
{
    struct Location;
    struct Token;
    class Parser;

    struct Type;
    struct PointerType;
    struct FunctionType;
    typedef std::shared_ptr<Type> TypePtr;
}
