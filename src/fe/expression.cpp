#include <cb/fe/Expression.hpp>

cb::fe::Expression::Expression(TypePtr type)
	: Type(type)
{
}

cb::fe::RegisterExpressionPtr cb::fe::RegisterExpression::Create(TypePtr type, const std::string& name)
{
	return std::make_shared<RegisterExpression>(type, name);
}

cb::fe::RegisterExpression::RegisterExpression(TypePtr type, const std::string& name)
	: Expression(type), Name(name)
{
}

cb::fe::SymbolExpressionPtr cb::fe::SymbolExpression::Create(TypePtr type, const std::string& name)
{
	return std::make_shared<SymbolExpression>(type, name);
}

cb::fe::SymbolExpression::SymbolExpression(TypePtr type, const std::string& name)
	: Expression(type), Name(name)
{
}

cb::fe::ConstExpressionPtr cb::fe::ConstExpression::Create(TypePtr type, const std::string& value)
{
	return std::make_shared<ConstExpression>(type, value);
}

cb::fe::ConstExpression::ConstExpression(TypePtr type, const std::string& value)
	: Expression(type), Value(value)
{
}

cb::fe::OperationExpressionPtr cb::fe::OperationExpression::Create(TypePtr type, const std::string& operation, const std::vector<ExpressionPtr>& args)
{
	return std::make_shared<OperationExpression>(type, operation, args);
}

cb::fe::OperationExpression::OperationExpression(TypePtr type, const std::string& operation, const std::vector<ExpressionPtr>& args)
	: Expression(type), Operation(operation), Args(args)
{
}