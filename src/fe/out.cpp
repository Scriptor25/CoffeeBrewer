#include <cb/Frontend.hpp>
#include <cb/fe/Expression.hpp>
#include <cb/fe/Statement.hpp>
#include <cb/fe/Symbol.hpp>
#include <cb/fe/Type.hpp>

#include <iostream>
#include <stdexcept>

std::ostream& cb::fe::operator<<(std::ostream& out, const SymbolPtr& ptr)
{
	if (!ptr)
		return out << "NULL";

	out << ptr->Type << " @" << ptr->Name;

	if (const auto p = std::dynamic_pointer_cast<GlobalVariable>(ptr))
		return out << *p;
	if (const auto p = std::dynamic_pointer_cast<Function>(ptr))
		return out << *p;

	throw std::runtime_error("not yet implemented");
}

std::ostream& cb::fe::operator<<(std::ostream& out, const GlobalVariable& var)
{
	return out << " = " << var.Initializer;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const Function& fun)
{
	out << "(";
	for (size_t i = 0; i < fun.Args.size(); i++)
	{
		if (i > 0) out << ", ";
		out << "%" << fun.Args[i];
	}
	out << ")";
	if (fun.Body.empty() && fun.Labels.empty())
		return out;
	out << std::endl << "{" << std::endl;
	for (const auto& statement : fun.Body)
		out << "\t" << statement << std::endl;
	for (const auto& label : fun.Labels)
		out << *label;
	return out << "}";
}

std::ostream& cb::fe::operator<<(std::ostream& out, const Label& lbl)
{
	out << "$" << lbl.Name << ":" << std::endl;
	for (const auto& statement : lbl.Body)
		out << "\t" << statement << std::endl;
	return out;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const TypePtr& ptr)
{
	return out << ptr->Name;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const StatementPtr& ptr)
{
	if (!ptr)
		return out << "NULL";

	if (const auto p = std::dynamic_pointer_cast<RegisterStatement>(ptr))
		return out << *p;
	if (const auto p = std::dynamic_pointer_cast<ReturnStatement>(ptr))
		return out << *p;
	if (const auto p = std::dynamic_pointer_cast<BranchStatement>(ptr))
		return out << *p;

	if (const auto p = std::dynamic_pointer_cast<Expression>(ptr))
		return out << p;

	throw std::runtime_error("not yet implemented");
}

std::ostream& cb::fe::operator<<(std::ostream& out, const RegisterStatement& reg)
{
	return out << "%" << reg.Name << " = " << reg.Initializer;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const ReturnStatement& ret)
{
	return out << "ret " << ret.Value;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const BranchStatement& brk)
{
	out << "br " << brk.Index;
	for (const auto& label : brk.Labels)
		out << ", $" << label;
	return out;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const ExpressionPtr& ptr)
{
	if (!ptr)
		return out << "NULL";

	out << ptr->Type;

	if (const auto p = std::dynamic_pointer_cast<RegisterExpression>(ptr))
		return out << *p;
	if (const auto p = std::dynamic_pointer_cast<SymbolExpression>(ptr))
		return out << *p;
	if (const auto p = std::dynamic_pointer_cast<ConstExpression>(ptr))
		return out << *p;
	if (const auto p = std::dynamic_pointer_cast<OperationExpression>(ptr))
		return out << *p;

	throw std::runtime_error("not yet implemented");
}

std::ostream& cb::fe::operator<<(std::ostream& out, const RegisterExpression& reg)
{
	return out << " %" << reg.Name;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const SymbolExpression& sym)
{
	return out << " @" << sym.Name;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const ConstExpression& cnt)
{
	out << " const ";
	if (cnt.CnstType == ConstType_Char) out << "'";
	if (cnt.CnstType == ConstType_String) out << "\"";
	out << cnt.Value;
	if (cnt.CnstType == ConstType_Char) out << "'";
	if (cnt.CnstType == ConstType_String) out << "\"";
	return out;
}

std::ostream& cb::fe::operator<<(std::ostream& out, const OperationExpression& opn)
{
	out << " " << opn.Operation;
	for (size_t i = 0; i < opn.Args.size(); i++)
	{
		if (i > 0) out << ",";
		out << " " << opn.Args[i];
	}
	return out;
}
