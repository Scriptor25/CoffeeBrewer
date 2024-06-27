#include <vector>
#include <cb/frontend/Instruction.hpp>
#include <cb/frontend/Parser.hpp>

cb::frontend::InstructionPtr cb::frontend::Parser::NextExpression(const std::string& reg)
{
    const auto where = m_Token.Where;
    const auto type = NextType();

    if (At(TokenType_SymbolName))
    {
        const auto name = Expect(TokenType_SymbolName).Value;
        return std::make_shared<SymbolInstruction>(where, reg, type, name);
    }

    if (At(TokenType_RegisterName))
    {
        const auto name = Expect(TokenType_RegisterName).Value;
        return std::make_shared<GetRegisterInstruction>(where, reg, type, name);
    }

    if (SkipIfAt("const"))
    {
        const auto [Where, Type, Value] = m_Token;
        NextToken();
        return std::make_shared<ConstInstruction>(where, reg, type, Type, Value);
    }

    if (SkipIfAt("load"))
    {
        const auto base = NextExpression("#0");
        Expect(TokenType_Comma);
        const auto offset = NextExpression("#1");
        return std::make_shared<LoadInstruction>(where, reg, type, base, offset);
    }

    if (SkipIfAt("call"))
    {
        const auto callee = NextExpression("#0");
        std::vector<InstructionPtr> args;
        size_t n = 1;
        while (At(TokenType_Comma))
        {
            Expect(TokenType_Comma);
            args.push_back(NextExpression("#" + std::to_string(n++)));
        }
        return std::make_shared<CallInstruction>(where, reg, type, callee, args);
    }

    if (SkipIfAt("alloca"))
    {
        const auto element_type = NextType();
        Expect(TokenType_Comma);
        const auto count = NextExpression("#0");
        return std::make_shared<AllocaInstruction>(where, reg, type, element_type, count);
    }

    if (SkipIfAt("op"))
    {
        const auto op = Expect(TokenType_ID).Value;
        std::vector<InstructionPtr> ops;
        size_t n = 0;
        while (At(TokenType_Comma))
        {
            Expect(TokenType_Comma);
            ops.push_back(NextExpression("#" + std::to_string(n++)));
        }
        return std::make_shared<OperationInstruction>(where, reg, type, op, ops);
    }

    throw std::runtime_error("not implemented");
}
