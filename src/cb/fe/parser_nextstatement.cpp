#include <cb/fe/parser.hpp>
#include <cb/fe/statement.hpp>

cb::fe::StatementPtr cb::fe::Parser::NextStatement()
{
    if (At(TokenType_RegisterName)) return NextRegisterStatement();
    if (At(TokenType_LabelName)) return NextLabelStatement();
    if (At("ret")) return NextReturnStatement();
    if (At("store")) return NextStoreStatement();
    if (At("br")) return NextBranchStatment();

    throw std::runtime_error("not implemented");
}

cb::fe::StatementPtr cb::fe::Parser::NextRegisterStatement()
{
    const auto where = m_Token.Where;
    const auto name = Expect(TokenType_RegisterName).Value;
    Expect(TokenType_Equal);
    const auto value = NextExpression();
    return std::make_shared<RegisterStatement>(where, name, value);
}

cb::fe::StatementPtr cb::fe::Parser::NextLabelStatement()
{
    const auto where = m_Token.Where;
    const auto name = Expect(TokenType_LabelName).Value;
    Expect(TokenType_Colon);
    return std::make_shared<LabelStatement>(where, name);
}

cb::fe::StatementPtr cb::fe::Parser::NextReturnStatement()
{
    const auto where = m_Token.Where;
    Expect("ret");

    if (SkipIfAt("void"))
        return std::make_shared<ReturnStatement>(where, nullptr);

    const auto value = NextExpression();
    return std::make_shared<ReturnStatement>(where, value);
}

cb::fe::StatementPtr cb::fe::Parser::NextStoreStatement()
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

cb::fe::StatementPtr cb::fe::Parser::NextBranchStatment()
{
    const auto where = m_Token.Where;
    Expect("br");
    const auto condition = NextExpression();
    Expect(TokenType_Comma);
    const auto destination = Expect(TokenType_LabelName).Value;
    return std::make_shared<BranchStatement>(where, condition, destination);
}
