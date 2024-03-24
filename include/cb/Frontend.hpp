#pragma once

#include <memory>

namespace cb::fe
{
	class Parser;

	enum TokenType
	{
		TokenType_ = 0b0000000,

		TokenType_EOF = 0b0000001,
		TokenType_Identifier = 0b0000010,
		TokenType_Integer = 0b0000100,
		TokenType_Float = 0b0001000,
		TokenType_String = 0b0010000,
		TokenType_Char = 0b0100000,
		TokenType_Other = 0b1000000,
	};
	std::ostream& operator<<(std::ostream& out, const TokenType& type);

	struct Token;
	std::ostream& operator<<(std::ostream& out, const Token& token);

	struct Symbol;
	typedef std::shared_ptr<Symbol> SymbolPtr;

	struct GlobalVariable;
	typedef std::shared_ptr<GlobalVariable> GlobalVariablePtr;

	struct Function;
	typedef std::shared_ptr<Function> FunctionPtr;

	struct Arg;
	typedef std::shared_ptr<Arg> ArgPtr;

	struct Type;
	typedef std::shared_ptr<Type> TypePtr;

	struct PointerType;
	typedef std::shared_ptr<PointerType> PointerTypePtr;

	struct ArrayType;
	typedef std::shared_ptr<ArrayType> ArrayTypePtr;

	struct FunctionType;
	typedef std::shared_ptr<FunctionType> FunctionTypePtr;

	struct Statement;
	typedef std::shared_ptr<Statement> StatementPtr;

	struct RegisterStatement;
	typedef std::shared_ptr<RegisterStatement> RegisterStatementPtr;

	struct ReturnStatement;
	typedef std::shared_ptr<ReturnStatement> ReturnStatementPtr;

	struct BranchStatement;
	typedef std::shared_ptr<BranchStatement> BranchStatementPtr;

	struct Expression;
	typedef std::shared_ptr<Expression> ExpressionPtr;

	struct RegisterExpression;
	typedef std::shared_ptr<RegisterExpression> RegisterExpressionPtr;

	struct SymbolExpression;
	typedef std::shared_ptr<SymbolExpression> SymbolExpressionPtr;

	struct ConstExpression;
	typedef std::shared_ptr<ConstExpression> ConstExpressionPtr;

	struct OperationExpression;
	typedef std::shared_ptr<OperationExpression> OperationExpressionPtr;
}
