#include <map>
#include <cb/frontend/Instruction.hpp>
#include <cb/frontend/Parser.hpp>
#include <cb/frontend/Symbol.hpp>

cb::frontend::SymbolPtr cb::frontend::Parser::NextSymbol()
{
    const auto where = m_Token.Where;
    const auto type = NextType();
    std::map<std::string, std::string> mods;
    if (SkipIfAt(TokenType_BracketOpen))
    {
        while (!AtEOF() && !At(TokenType_BracketClose))
        {
            const auto key = Expect(TokenType_ID).Value;
            Expect(TokenType_Equal);
            const auto value = Expect(TokenType_ID).Value;
            mods[key] = value;
            if (!At(TokenType_BracketClose))
                Expect(TokenType_Comma);
        }
        Expect(TokenType_BracketClose);
    }
    const auto name = Expect(TokenType_SymbolName).Value;

    if (SkipIfAt(TokenType_Equal)) return NextVariableSymbol(where, type, mods, name);
    if (SkipIfAt(TokenType_ParenOpen)) return NextFunctionSymbol(where, type, mods, name);

    return std::make_shared<Symbol>(where, type, mods, name);
}

cb::frontend::SymbolPtr cb::frontend::Parser::NextVariableSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name)
{
    const auto value = NextExpression("");
    return std::make_shared<VariableSymbol>(where, type, mods, name, value);
}

cb::frontend::SymbolPtr cb::frontend::Parser::NextFunctionSymbol(const Location& where, const TypePtr& type, const std::map<std::string, std::string>& mods, const std::string& name)
{
    std::vector<std::string> args;
    while (!AtEOF() && !At(TokenType_ParenClose))
    {
        const auto arg = Expect(TokenType_RegisterName).Value;
        args.push_back(arg);
        if (!At(TokenType_ParenClose))
            Expect(TokenType_Comma);
    }
    Expect(TokenType_ParenClose);

    auto symbol = std::make_shared<FunctionSymbol>(where, type, mods, name, args);

    Expect(TokenType_BraceOpen);
    while (!AtEOF() && !At(TokenType_BraceClose))
    {
        const auto inst = NextStatement(symbol);
        if (const auto p = std::dynamic_pointer_cast<LabelInstruction>(inst))
            symbol->ActiveBlock = symbol->GetBlock(p->Name);
        else inst->InsertInto(symbol);
    }
    Expect(TokenType_BraceClose);

    return symbol;
}
