#include <cb/frontend/Instruction.hpp>
#include <cb/frontend/Parser.hpp>
#include <cb/frontend/Type.hpp>

#include "cb/frontend/Symbol.hpp"

cb::frontend::InstructionPtr cb::frontend::Parser::NextStatement(const FunctionSymbolPtr& parent)
{
    if (At(TokenType_LabelName)) return NextLabelStatement();
    if (At("ret")) return NextReturnStatement();
    if (At("store")) return NextStoreStatement();
    if (At("br")) return NextBranchStatment(parent);

    std::string reg;
    if (At(TokenType_RegisterName))
    {
        reg = Expect(TokenType_RegisterName).Value;
        Expect(TokenType_Equal);
    }
    return NextExpression(reg);
}

cb::frontend::InstructionPtr cb::frontend::Parser::NextLabelStatement()
{
    const auto where = m_Token.Where;
    const auto name = Expect(TokenType_LabelName).Value;
    Expect(TokenType_Colon);
    return std::make_shared<LabelInstruction>(where, name);
}

cb::frontend::InstructionPtr cb::frontend::Parser::NextReturnStatement()
{
    const auto where = m_Token.Where;
    Expect("ret");

    if (SkipIfAt("void"))
        return std::make_shared<ReturnInstruction>(where);

    const auto value = NextExpression("#0");
    return std::make_shared<ReturnInstruction>(where, value);
}

cb::frontend::InstructionPtr cb::frontend::Parser::NextStoreStatement()
{
    const auto where = m_Token.Where;
    Expect("store");
    const auto base = NextExpression("#0");
    Expect(TokenType_Comma);
    const auto offset = NextExpression("#1");
    Expect(TokenType_Comma);
    const auto value = NextExpression("#2");
    return std::make_shared<StoreInstruction>(where, base, offset, value);
}

cb::frontend::InstructionPtr cb::frontend::Parser::NextBranchStatment(const FunctionSymbolPtr& parent)
{
    const auto where = m_Token.Where;
    Expect("br");

    if (At(TokenType_LabelName))
    {
        const auto dest = Expect(TokenType_LabelName).Value;
        return std::make_shared<BranchInstruction>(where, parent->GetBlock(dest));
    }

    const auto condition = NextExpression("#0");
    Expect(TokenType_Comma);
    const auto dest_then = Expect(TokenType_LabelName).Value;
    Expect(TokenType_Comma);
    const auto dest_else = Expect(TokenType_LabelName).Value;
    return std::make_shared<ConditionBranchInstruction>(where, condition, parent->GetBlock(dest_then), parent->GetBlock(dest_else));
}
