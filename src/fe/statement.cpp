#include <cb/fe/Statement.hpp>

cb::fe::RegisterStatementPtr cb::fe::RegisterStatement::Create(const std::string& name, ExpressionPtr initializer)
{
	return std::make_shared<RegisterStatement>(name, initializer);
}

cb::fe::RegisterStatement::RegisterStatement(const std::string& name, ExpressionPtr initializer)
	: Name(name), Initializer(initializer)
{
}

cb::fe::ReturnStatementPtr cb::fe::ReturnStatement::Create(ExpressionPtr value)
{
	return std::make_shared<ReturnStatement>(value);
}

cb::fe::ReturnStatement::ReturnStatement(ExpressionPtr value)
	: Value(value)
{
}

cb::fe::BranchStatementPtr cb::fe::BranchStatement::Create(ExpressionPtr index, const std::vector<std::string>& labels)
{
	return std::make_shared<BranchStatement>(index, labels);
}

cb::fe::BranchStatement::BranchStatement(ExpressionPtr index, const std::vector<std::string>& labels)
	: Index(index), Labels(labels)
{
}
