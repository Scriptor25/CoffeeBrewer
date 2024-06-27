#pragma once

#include <memory>

namespace cb::backend
{
    struct Value;
    struct Int8Value;
    struct Int16Value;
    struct Int32Value;
    struct Int64Value;
    struct Float32Value;
    struct Float64Value;
    struct PointerValue;
    struct ConstPointerValue;
    typedef std::shared_ptr<Value> ValuePtr;

    class Runtime;
}
