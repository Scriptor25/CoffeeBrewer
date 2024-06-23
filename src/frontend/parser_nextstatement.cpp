#include <cb/frontend/Expression.hpp>
#include <cb/frontend/Parser.hpp>
#include <cb/frontend/Statement.hpp>

cb::frontend::StatementPtr cb::frontend::Parser::NextStatement()
{
    if (At(TokenType_RegisterName)) return NextRegisterStatement();
    if (At(TokenType_LabelName)) return NextLabelStatement();
    if (At("ret")) return NextReturnStatement();
    if (At("store")) return NextStoreStatement();
    if (At("br")) return NextBranchStatment();

    return NextExpression();
}

cb::frontend::StatementPtr cb::frontend::Parser::NextRegisterStatement()
{
    const auto where = m_Token.Where;
    const auto name = Expect(TokenType_RegisterName).Value;
    Expect(TokenType_Equal);
    const auto value = NextExpression();
    return std::make_shared<RegisterStatement>(where, name, value);
}

cb::frontend::StatementPtr cb::frontend::Parser::NextLabelStatement()
{
    const auto where = m_Token.Where;
    const auto name = Expect(TokenType_LabelName).Value;
    Expect(TokenType_Colon);
    return std::make_shared<LabelStatement>(where, name);
}

cb::frontend::StatementPtr cb::frontend::Parser::NextReturnStatement()
{
    const auto where = m_Token.Where;
    Expect("ret");

    if (SkipIfAt("void"))
        return std::make_shared<ReturnStatement>(where, nullptr);

    const auto value = NextExpression();
    return std::make_shared<ReturnStatement>(where, value);
}

cb::frontend::StatementPtr cb::frontend::Parser::NextStoreStatement()
{
    const auto where = m_Token.Where;
    Expect("store");
    const auto base = NextExpression();
    Expect(TokenType_Comma);
    const auto offset = NextExpression();
    Expect(TokenType_Comma);
    const auto value = NextExpression();
    return std::make_shared<StoreStatement>(where, base, offset, value);
}

cb::frontend::StatementPtr cb::frontend::Parser::NextBranchStatment()
{
    const auto where = m_Token.Where;
    Expect("br");
    if (At(TokenType_LabelName))
    {
        const auto dest = Expect(TokenType_LabelName).Value;
        return std::make_shared<BranchStatement>(where, dest);
    }

    const auto condition = NextExpression();
    Expect(TokenType_Comma);
    const auto dest_then = Expect(TokenType_LabelName).Value;
    Expect(TokenType_Comma);
    const auto dest_else = Expect(TokenType_LabelName).Value;
    return std::make_shared<ConditionedBranchStatement>(where, condition, dest_then, dest_else);
}
