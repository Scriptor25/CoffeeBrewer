#include <cb/fe/Parser.hpp>
#include <cb/fe/Type.hpp>

cb::fe::TypePtr cb::fe::Parser::NextType()
{
    auto name = Expect(TokenType_Identifier).Value;
    auto base = Type::Get(name);
    return NextType(base);
}

cb::fe::TypePtr cb::fe::Parser::NextType(TypePtr base)
{
    if (At("*")) return NextType(PointerType::Get(base));
    if (At("["))
    {
        auto size = Expect(TokenType_Integer).Value;
        return NextType(ArrayType::Get(base, std::stoull(size)));
    }
    return base;
}
