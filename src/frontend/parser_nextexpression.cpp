#include <vector>
#include <cb/frontend/Expression.hpp>
#include <cb/frontend/Parser.hpp>

cb::frontend::ExpressionPtr cb::frontend::Parser::NextExpression()
{
    const auto where = m_Token.Where;
    const auto type = NextType();

    if (At(TokenType_SymbolName))
    {
        const auto name = Expect(TokenType_SymbolName).Value;
        return std::make_shared<SymbolExpression>(where, type, name);
    }

    if (At(TokenType_RegisterName))
    {
        const auto name = Expect(TokenType_RegisterName).Value;
        return std::make_shared<RegisterExpression>(where, type, name);
    }

    if (SkipIfAt("const"))
    {
        const auto [Where, Type, Value] = m_Token;
        NextToken();
        return std::make_shared<ConstExpression>(where, type, Type, Value);
    }

    if (SkipIfAt("load"))
    {
        const auto base = NextExpression();
        Expect(TokenType_Comma);
        const auto offset = NextExpression();
        return std::make_shared<LoadExpression>(where, type, base, offset);
    }

    if (SkipIfAt("call"))
    {
        const auto callee = NextExpression();
        std::vector<ExpressionPtr> args;
        while (At(TokenType_Comma))
        {
            Expect(TokenType_Comma);
            args.push_back(NextExpression());
        }
        return std::make_shared<CallExpression>(where, type, callee, args);
    }

    if (SkipIfAt("alloca"))
    {
        const auto element_type = NextType();
        Expect(TokenType_Comma);
        const auto count = NextExpression();
        return std::make_shared<AllocaExpression>(where, type, element_type, count);
    }

    if (SkipIfAt("op"))
    {
        const auto op = Expect(TokenType_ID).Value;
        std::vector<ExpressionPtr> ops;
        while (At(TokenType_Comma))
        {
            Expect(TokenType_Comma);
            ops.push_back(NextExpression());
        }
        return std::make_shared<OperationExpression>(where, type, op, ops);
    }

    throw std::runtime_error("not implemented");
}
