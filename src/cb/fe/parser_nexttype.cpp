#include <vector>
#include <cb/fe/parser.hpp>
#include <cb/fe/type.hpp>

cb::fe::TypePtr cb::fe::Parser::NextType()
{
    const auto name = Expect(TokenType_ID).Value;
    auto base = Type::Get(name);

    while (true)
    {
        if (SkipIfAt(TokenType_Asterisk))
        {
            base = PointerType::Get(base);
            continue;
        }

        if (SkipIfAt(TokenType_ParenOpen))
        {
            std::vector<TypePtr> args;
            bool is_varargs = false;
            while (!AtEOF() && !At(TokenType_ParenClose))
            {
                if (SkipIfAt(TokenType_Period))
                {
                    Expect(TokenType_Period);
                    Expect(TokenType_Period);
                    is_varargs = true;
                    break;
                }
                args.push_back(NextType());
                if (!At(TokenType_ParenClose))
                    Expect(TokenType_Comma);
            }
            Expect(TokenType_ParenClose);

            base = FunctionType::Get(base, args, is_varargs);
            continue;
        }

        return base;
    }
}
