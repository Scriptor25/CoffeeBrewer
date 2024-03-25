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
	std::ostream& operator<<(std::ostream& out, const SymbolPtr& ptr);

	struct GlobalVariable;
	typedef std::shared_ptr<GlobalVariable> GlobalVariablePtr;
	std::ostream& operator<<(std::ostream& out, const GlobalVariable& var);

	struct Insertable;
	typedef std::shared_ptr<Insertable> InsertablePtr;

	struct Function;
	typedef std::shared_ptr<Function> FunctionPtr;
	std::ostream& operator<<(std::ostream& out, const Function& fun);

	struct Label;
	typedef std::shared_ptr<Label> LabelPtr;
	std::ostream& operator<<(std::ostream& out, const Label& lbl);

	struct Type;
	typedef std::shared_ptr<Type> TypePtr;
	std::ostream& operator<<(std::ostream& out, const TypePtr& ptr);

	struct PointerType;
	typedef std::shared_ptr<PointerType> PointerTypePtr;

	struct ArrayType;
	typedef std::shared_ptr<ArrayType> ArrayTypePtr;

	struct FunctionType;
	typedef std::shared_ptr<FunctionType> FunctionTypePtr;

	struct Statement;
	typedef std::shared_ptr<Statement> StatementPtr;
	std::ostream& operator<<(std::ostream& out, const StatementPtr& ptr);

	struct RegisterStatement;
	typedef std::shared_ptr<RegisterStatement> RegisterStatementPtr;
	std::ostream& operator<<(std::ostream& out, const RegisterStatement& reg);

	struct ReturnStatement;
	typedef std::shared_ptr<ReturnStatement> ReturnStatementPtr;
	std::ostream& operator<<(std::ostream& out, const ReturnStatement& ret);

	struct BranchStatement;
	typedef std::shared_ptr<BranchStatement> BranchStatementPtr;
	std::ostream& operator<<(std::ostream& out, const BranchStatement& brk);

	struct Expression;
	typedef std::shared_ptr<Expression> ExpressionPtr;
	std::ostream& operator<<(std::ostream& out, const ExpressionPtr& ptr);

	struct RegisterExpression;
	typedef std::shared_ptr<RegisterExpression> RegisterExpressionPtr;
	std::ostream& operator<<(std::ostream& out, const RegisterExpression& reg);

	struct SymbolExpression;
	typedef std::shared_ptr<SymbolExpression> SymbolExpressionPtr;
	std::ostream& operator<<(std::ostream& out, const SymbolExpression& sym);

	enum ConstType
	{
		ConstType_,
		ConstType_Integer,
		ConstType_Float,
		ConstType_Char,
		ConstType_String,
	};
	struct ConstExpression;
	typedef std::shared_ptr<ConstExpression> ConstExpressionPtr;
	std::ostream& operator<<(std::ostream& out, const ConstExpression& cnt);

	struct OperationExpression;
	typedef std::shared_ptr<OperationExpression> OperationExpressionPtr;
	std::ostream& operator<<(std::ostream& out, const OperationExpression& opn);
}
