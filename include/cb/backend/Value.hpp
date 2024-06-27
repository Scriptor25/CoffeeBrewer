#pragma once

#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <cb/backend/Backend.hpp>

namespace cb::backend
{
    template <typename T>
    T As(const Value*) { throw std::runtime_error("not implemented"); }

    template <>
    int8_t As(const Value*);
    template <>
    int16_t As(const Value*);
    template <>
    int32_t As(const Value*);
    template <>
    int64_t As(const Value*);
    template <>
    float_t As(const Value*);
    template <>
    double_t As(const Value*);
    template <>
    void* As(const Value*);
    template <>
    const void* As(const Value*);

    struct Value
    {
        virtual ~Value();

        template <typename T>
        [[nodiscard]] T As() const { return backend::As<T>(this); }

        [[nodiscard]] virtual int8_t AsInt8() const = 0;
        [[nodiscard]] virtual int16_t AsInt16() const = 0;
        [[nodiscard]] virtual int32_t AsInt32() const = 0;
        [[nodiscard]] virtual int64_t AsInt64() const = 0;
        [[nodiscard]] virtual float_t AsFloat32() const = 0;
        [[nodiscard]] virtual double_t AsFloat64() const = 0;
        [[nodiscard]] virtual void* AsPointer() const = 0;
        [[nodiscard]] virtual const void* AsConstPointer() const = 0;

        [[nodiscard]] bool AsBool() const;
    };

    struct Int8Value : Value
    {
        Int8Value();
        explicit Int8Value(int8_t value);
        Int8Value(const void* base, int64_t offset);

        [[nodiscard]] int8_t AsInt8() const override;
        [[nodiscard]] int16_t AsInt16() const override;
        [[nodiscard]] int32_t AsInt32() const override;
        [[nodiscard]] int64_t AsInt64() const override;
        [[nodiscard]] float_t AsFloat32() const override;
        [[nodiscard]] double_t AsFloat64() const override;
        [[nodiscard]] void* AsPointer() const override;
        [[nodiscard]] const void* AsConstPointer() const override;

        int8_t Value = 0;
    };

    struct Int16Value : Value
    {
        Int16Value();
        explicit Int16Value(int16_t value);
        Int16Value(const void* base, int64_t offset);

        [[nodiscard]] int8_t AsInt8() const override;
        [[nodiscard]] int16_t AsInt16() const override;
        [[nodiscard]] int32_t AsInt32() const override;
        [[nodiscard]] int64_t AsInt64() const override;
        [[nodiscard]] float_t AsFloat32() const override;
        [[nodiscard]] double_t AsFloat64() const override;
        [[nodiscard]] void* AsPointer() const override;
        [[nodiscard]] const void* AsConstPointer() const override;

        int16_t Value = 0;
    };

    struct Int32Value : Value
    {
        Int32Value();
        explicit Int32Value(int32_t value);
        Int32Value(const void* base, int64_t offset);

        [[nodiscard]] int8_t AsInt8() const override;
        [[nodiscard]] int16_t AsInt16() const override;
        [[nodiscard]] int32_t AsInt32() const override;
        [[nodiscard]] int64_t AsInt64() const override;
        [[nodiscard]] float_t AsFloat32() const override;
        [[nodiscard]] double_t AsFloat64() const override;
        [[nodiscard]] void* AsPointer() const override;
        [[nodiscard]] const void* AsConstPointer() const override;

        int32_t Value = 0;
    };

    struct Int64Value : Value
    {
        Int64Value();
        explicit Int64Value(int64_t value);
        Int64Value(const void* base, int64_t offset);

        [[nodiscard]] int8_t AsInt8() const override;
        [[nodiscard]] int16_t AsInt16() const override;
        [[nodiscard]] int32_t AsInt32() const override;
        [[nodiscard]] int64_t AsInt64() const override;
        [[nodiscard]] float_t AsFloat32() const override;
        [[nodiscard]] double_t AsFloat64() const override;
        [[nodiscard]] void* AsPointer() const override;
        [[nodiscard]] const void* AsConstPointer() const override;

        int64_t Value = 0;
    };

    struct Float32Value : Value
    {
        Float32Value();
        explicit Float32Value(float_t value);
        Float32Value(const void* base, int64_t offset);

        [[nodiscard]] int8_t AsInt8() const override;
        [[nodiscard]] int16_t AsInt16() const override;
        [[nodiscard]] int32_t AsInt32() const override;
        [[nodiscard]] int64_t AsInt64() const override;
        [[nodiscard]] float_t AsFloat32() const override;
        [[nodiscard]] double_t AsFloat64() const override;
        [[nodiscard]] void* AsPointer() const override;
        [[nodiscard]] const void* AsConstPointer() const override;

        float_t Value = 0.0f;
    };

    struct Float64Value : Value
    {
        Float64Value();
        explicit Float64Value(double_t value);
        Float64Value(const void* base, int64_t offset);

        [[nodiscard]] int8_t AsInt8() const override;
        [[nodiscard]] int16_t AsInt16() const override;
        [[nodiscard]] int32_t AsInt32() const override;
        [[nodiscard]] int64_t AsInt64() const override;
        [[nodiscard]] float_t AsFloat32() const override;
        [[nodiscard]] double_t AsFloat64() const override;
        [[nodiscard]] void* AsPointer() const override;
        [[nodiscard]] const void* AsConstPointer() const override;

        double_t Value = 0.0;
    };

    struct PointerValue : Value
    {
        PointerValue();
        explicit PointerValue(void* value);
        PointerValue(const void* base, int64_t offset);

        [[nodiscard]] int8_t AsInt8() const override;
        [[nodiscard]] int16_t AsInt16() const override;
        [[nodiscard]] int32_t AsInt32() const override;
        [[nodiscard]] int64_t AsInt64() const override;
        [[nodiscard]] float_t AsFloat32() const override;
        [[nodiscard]] double_t AsFloat64() const override;
        [[nodiscard]] void* AsPointer() const override;
        [[nodiscard]] const void* AsConstPointer() const override;

        void* Value = nullptr;
    };

    struct ConstPointerValue : Value
    {
        ConstPointerValue();
        explicit ConstPointerValue(const void* value);
        ConstPointerValue(const void* base, int64_t offset);

        [[nodiscard]] int8_t AsInt8() const override;
        [[nodiscard]] int16_t AsInt16() const override;
        [[nodiscard]] int32_t AsInt32() const override;
        [[nodiscard]] int64_t AsInt64() const override;
        [[nodiscard]] float_t AsFloat32() const override;
        [[nodiscard]] double_t AsFloat64() const override;
        [[nodiscard]] void* AsPointer() const override;
        [[nodiscard]] const void* AsConstPointer() const override;

        const void* Value = nullptr;
    };
}
