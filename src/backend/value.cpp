#include <cb/backend/Value.hpp>

template <>
int8_t cb::backend::As<int8_t>(const Value* value) { return value->AsInt8(); }

template <>
int16_t cb::backend::As<int16_t>(const Value* value) { return value->AsInt16(); }

template <>
int32_t cb::backend::As<int32_t>(const Value* value) { return value->AsInt32(); }

template <>
int64_t cb::backend::As<int64_t>(const Value* value) { return value->AsInt64(); }

template <>
float_t cb::backend::As<float_t>(const Value* value) { return value->AsFloat32(); }

template <>
double_t cb::backend::As<double_t>(const Value* value) { return value->AsFloat64(); }

template <>
void* cb::backend::As<void*>(const Value* value) { return value->AsPointer(); }

template <>
const void* cb::backend::As<const void*>(const Value* value) { return value->AsConstPointer(); }

cb::backend::Value::~Value() = default;

bool cb::backend::Value::AsBool() const
{
    return AsInt8() != 0;
}

cb::backend::Int8Value::Int8Value() = default;

cb::backend::Int8Value::Int8Value(const int8_t value)
    : Value(value)
{
}

cb::backend::Int8Value::Int8Value(const void* base, const int64_t offset)
    : Value(((int8_t*)base)[offset])
{
}

int8_t cb::backend::Int8Value::AsInt8() const
{
    return Value;
}

int16_t cb::backend::Int8Value::AsInt16() const
{
    return Value;
}

int32_t cb::backend::Int8Value::AsInt32() const
{
    return Value;
}

int64_t cb::backend::Int8Value::AsInt64() const
{
    return Value;
}

float_t cb::backend::Int8Value::AsFloat32() const
{
    return Value;
}

double_t cb::backend::Int8Value::AsFloat64() const
{
    return Value;
}

void* cb::backend::Int8Value::AsPointer() const
{
    return reinterpret_cast<void*>(static_cast<intptr_t>(Value));
}

const void* cb::backend::Int8Value::AsConstPointer() const
{
    return reinterpret_cast<const void*>(static_cast<intptr_t>(Value));
}

cb::backend::Int16Value::Int16Value() = default;

cb::backend::Int16Value::Int16Value(const int16_t value)
    : Value(value)
{
}

cb::backend::Int16Value::Int16Value(const void* base, const int64_t offset)
    : Value(((int16_t*)base)[offset])
{
}

int8_t cb::backend::Int16Value::AsInt8() const
{
    return static_cast<int8_t>(Value);
}

int16_t cb::backend::Int16Value::AsInt16() const
{
    return Value;
}

int32_t cb::backend::Int16Value::AsInt32() const
{
    return Value;
}

int64_t cb::backend::Int16Value::AsInt64() const
{
    return Value;
}

float_t cb::backend::Int16Value::AsFloat32() const
{
    return Value;
}

double_t cb::backend::Int16Value::AsFloat64() const
{
    return Value;
}

void* cb::backend::Int16Value::AsPointer() const
{
    return reinterpret_cast<void*>(static_cast<intptr_t>(Value));
}

const void* cb::backend::Int16Value::AsConstPointer() const
{
    return reinterpret_cast<const void*>(static_cast<intptr_t>(Value));
}

cb::backend::Int32Value::Int32Value() = default;

cb::backend::Int32Value::Int32Value(const int32_t value)
    : Value(value)
{
}

cb::backend::Int32Value::Int32Value(const void* base, const int64_t offset)
    : Value(((int32_t*)base)[offset])
{
}

int8_t cb::backend::Int32Value::AsInt8() const
{
    return static_cast<int8_t>(Value);
}

int16_t cb::backend::Int32Value::AsInt16() const
{
    return static_cast<int16_t>(Value);
}

int32_t cb::backend::Int32Value::AsInt32() const
{
    return Value;
}

int64_t cb::backend::Int32Value::AsInt64() const
{
    return Value;
}

float_t cb::backend::Int32Value::AsFloat32() const
{
    return static_cast<float_t>(Value);
}

double_t cb::backend::Int32Value::AsFloat64() const
{
    return Value;
}

void* cb::backend::Int32Value::AsPointer() const
{
    return reinterpret_cast<void*>(static_cast<intptr_t>(Value));
}

const void* cb::backend::Int32Value::AsConstPointer() const
{
    return reinterpret_cast<const void*>(static_cast<intptr_t>(Value));
}

cb::backend::Int64Value::Int64Value() = default;

cb::backend::Int64Value::Int64Value(const int64_t value)
    : Value(value)
{
}

cb::backend::Int64Value::Int64Value(const void* base, const int64_t offset)
    : Value(((int64_t*)base)[offset])
{
}

int8_t cb::backend::Int64Value::AsInt8() const
{
    return static_cast<int8_t>(Value);
}

int16_t cb::backend::Int64Value::AsInt16() const
{
    return static_cast<int16_t>(Value);
}

int32_t cb::backend::Int64Value::AsInt32() const
{
    return static_cast<int32_t>(Value);
}

int64_t cb::backend::Int64Value::AsInt64() const
{
    return Value;
}

float_t cb::backend::Int64Value::AsFloat32() const
{
    return static_cast<float_t>(Value);
}

double_t cb::backend::Int64Value::AsFloat64() const
{
    return static_cast<double_t>(Value);
}

void* cb::backend::Int64Value::AsPointer() const
{
    return reinterpret_cast<void*>(static_cast<intptr_t>(Value));
}

const void* cb::backend::Int64Value::AsConstPointer() const
{
    return reinterpret_cast<const void*>(static_cast<intptr_t>(Value));
}

cb::backend::Float32Value::Float32Value() = default;

cb::backend::Float32Value::Float32Value(const float_t value)
    : Value(value)
{
}

cb::backend::Float32Value::Float32Value(const void* base, const int64_t offset)
    : Value(((float_t*)base)[offset])
{
}

int8_t cb::backend::Float32Value::AsInt8() const
{
    return static_cast<int8_t>(Value);
}

int16_t cb::backend::Float32Value::AsInt16() const
{
    return static_cast<int16_t>(Value);
}

int32_t cb::backend::Float32Value::AsInt32() const
{
    return static_cast<int32_t>(Value);
}

int64_t cb::backend::Float32Value::AsInt64() const
{
    return static_cast<int64_t>(Value);
}

float_t cb::backend::Float32Value::AsFloat32() const
{
    return Value;
}

double_t cb::backend::Float32Value::AsFloat64() const
{
    return Value;
}

void* cb::backend::Float32Value::AsPointer() const
{
    return reinterpret_cast<void*>(static_cast<intptr_t>(Value));
}

const void* cb::backend::Float32Value::AsConstPointer() const
{
    return reinterpret_cast<const void*>(static_cast<intptr_t>(Value));
}

cb::backend::Float64Value::Float64Value() = default;

cb::backend::Float64Value::Float64Value(const double_t value)
    : Value(value)
{
}

cb::backend::Float64Value::Float64Value(const void* base, const int64_t offset)
    : Value(((double_t*)base)[offset])
{
}

int8_t cb::backend::Float64Value::AsInt8() const
{
    return static_cast<int8_t>(Value);
}

int16_t cb::backend::Float64Value::AsInt16() const
{
    return static_cast<int16_t>(Value);
}

int32_t cb::backend::Float64Value::AsInt32() const
{
    return static_cast<int32_t>(Value);
}

int64_t cb::backend::Float64Value::AsInt64() const
{
    return static_cast<int64_t>(Value);
}

float_t cb::backend::Float64Value::AsFloat32() const
{
    return static_cast<float_t>(Value);
}

double_t cb::backend::Float64Value::AsFloat64() const
{
    return Value;
}

void* cb::backend::Float64Value::AsPointer() const
{
    return reinterpret_cast<void*>(static_cast<intptr_t>(Value));
}

const void* cb::backend::Float64Value::AsConstPointer() const
{
    return reinterpret_cast<const void*>(static_cast<intptr_t>(Value));
}

cb::backend::PointerValue::PointerValue() = default;

cb::backend::PointerValue::PointerValue(void* value)
    : Value(value)
{
}

cb::backend::PointerValue::PointerValue(const void* base, const int64_t offset)
    : Value(((void**)base)[offset])
{
}

int8_t cb::backend::PointerValue::AsInt8() const
{
    return static_cast<int8_t>(reinterpret_cast<intptr_t>(Value));
}

int16_t cb::backend::PointerValue::AsInt16() const
{
    return static_cast<int16_t>(reinterpret_cast<intptr_t>(Value));
}

int32_t cb::backend::PointerValue::AsInt32() const
{
    return static_cast<int32_t>(reinterpret_cast<intptr_t>(Value));
}

int64_t cb::backend::PointerValue::AsInt64() const
{
    return reinterpret_cast<intptr_t>(Value);
}

float_t cb::backend::PointerValue::AsFloat32() const
{
    return static_cast<float_t>(reinterpret_cast<intptr_t>(Value));
}

double_t cb::backend::PointerValue::AsFloat64() const
{
    return static_cast<double_t>(reinterpret_cast<intptr_t>(Value));
}

void* cb::backend::PointerValue::AsPointer() const
{
    return Value;
}

const void* cb::backend::PointerValue::AsConstPointer() const
{
    return Value;
}

cb::backend::ConstPointerValue::ConstPointerValue() = default;

cb::backend::ConstPointerValue::ConstPointerValue(const void* value)
    : Value(value)
{
}

cb::backend::ConstPointerValue::ConstPointerValue(const void* base, const int64_t offset)
    : Value(((const void**)base)[offset])
{
}

int8_t cb::backend::ConstPointerValue::AsInt8() const
{
    return static_cast<int8_t>(reinterpret_cast<intptr_t>(Value));
}

int16_t cb::backend::ConstPointerValue::AsInt16() const
{
    return static_cast<int16_t>(reinterpret_cast<intptr_t>(Value));
}

int32_t cb::backend::ConstPointerValue::AsInt32() const
{
    return static_cast<int32_t>(reinterpret_cast<intptr_t>(Value));
}

int64_t cb::backend::ConstPointerValue::AsInt64() const
{
    return reinterpret_cast<intptr_t>(Value);
}

float_t cb::backend::ConstPointerValue::AsFloat32() const
{
    return static_cast<float_t>(reinterpret_cast<intptr_t>(Value));
}

double_t cb::backend::ConstPointerValue::AsFloat64() const
{
    return static_cast<double_t>(reinterpret_cast<intptr_t>(Value));
}

void* cb::backend::ConstPointerValue::AsPointer() const
{
    return const_cast<void*>(Value);
}

const void* cb::backend::ConstPointerValue::AsConstPointer() const
{
    return Value;
}
