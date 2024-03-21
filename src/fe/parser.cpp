#include <cb/fe/Arg.hpp>
#include <cb/fe/Parser.hpp>
#include <cb/fe/Statement.hpp>

#include <iostream>

#include "cb/fe/Type.hpp"

bool cb::fe::Parser::Parse(std::istream &stream)
{
    if (!stream)
        return false;

    Parser parser(stream);

    for (parser.Next(); !parser.AtEOF(); parser.Next())
    {
        parser.NextStatement();
        // std::cout << parser.m_Token << std::endl;
    }

    return true;
}

cb::fe::Parser::Parser(std::istream &stream)
    : m_Stream(stream) {}

cb::fe::StatementPtr cb::fe::Parser::NextStatement()
{
    if (At("%")) return NextRegisterStatement();
    // if (At("$")) return NextLabel();
    if (At("ret")) return NextReturnStatement();
    if (At("br")) return NextBreakStatement();

    const auto type = NextType();
    Expect("@");
    const auto name = Expect(TokenType_Identifier).Value;
    if (At("(")) return NextFunctionDeclaration(type, name);
    if (At("=")) return NextSymbolStatement(type, name);

    throw std::runtime_error("unexpected token");
}

cb::fe::FunctionDeclarationPtr cb::fe::Parser::NextFunctionDeclaration(TypePtr type, const std::string &name)
{
    Expect("(");

    std::vector<ArgPtr> args;
    while (!At(")") && !AtEOF())
    {
        const auto atype = NextType();
        const auto arg = Arg::Get(atype);
        if (At("%"))
        {
            Next();
            arg->Name = Expect(TokenType_Identifier).Value;
        }

        if (!At(")"))
            Expect(",");
    }
    Expect(")");

    std::vector<TypePtr> argtypes(args.size());
    for (const auto &arg: args)
        argtypes.push_back(arg->Type);
    const auto functype = FunctionType::Get(type, argtypes);

    if (At("{"))
        return NextFunctionDefinition(functype, name, args);

    return FunctionDeclaration::Get(name, functype);
}

cb::fe::FunctionDefinitionPtr cb::fe::Parser::NextFunctionDefinition(FunctionTypePtr type, const std::string &name,
                                                                     const std::vector<ArgPtr> &args)
{
    Expect("{");
    while (!At("}") && !AtEOF()) NextStatement(); // TODO: add to function body
    Expect("}");

    throw std::runtime_error("not yet implemented");
}

cb::fe::ReturnStatementPtr cb::fe::Parser::NextReturnStatement() { throw std::runtime_error("not yet implemented"); }

cb::fe::BreakStatementPtr cb::fe::Parser::NextBreakStatement() { throw std::runtime_error("not yet implemented"); }

cb::fe::SymbolStatementPtr cb::fe::Parser::NextSymbolStatement(TypePtr type, const std::string &name)
{
    Expect("=");
    auto initializer = NextExpression();
    return SymbolStatement::Get(name, type, initializer);
}

cb::fe::RegisterStatementPtr cb::fe::Parser::NextRegisterStatement()
{
    throw std::runtime_error("not yet implemented");
}

cb::fe::ExpressionPtr cb::fe::Parser::NextExpression()
{
    if (NextIfAt("const"))
    {

    }
}
